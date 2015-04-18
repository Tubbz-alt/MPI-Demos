/**
 * @file    Spawn_Demo_Common.cpp
 * @author  Marvin Smith
 * @date    4/17/2015
 */
#include "Spawn_Demo_Common.hpp"


// C++ Standard Libraries
#include <cstdlib>
#include <iostream>
#include <unistd.h>

// MPI Libraries
#include <mpi.h>

using namespace std;


/**
 * Get a process name by pid.
 */
const char* get_process_name_by_pid(const int pid)
{

    char* name = (char*)calloc(1024,sizeof(char));
    if(name){
        sprintf(name, "/proc/%d/cmdline",pid);
        FILE* f = fopen(name,"r");

        if(f){

            size_t size;
            size = fread(name, sizeof(char), 1024, f);

            if(size>0){
                if('\n'==name[size-1])

                    name[size-1]='\0';

            }
            fclose(f);
        }
    }
    return name;
}




/**
 * Constructor
 */
Segfault_Message::Segfault_Message()
{
    Allocate_Buffer();
}


/**
 * Segmentation Fault Message Constructor
 */
Segfault_Message::Segfault_Message( const int& rank, 
                                    const int& should_reboot )
  : m_rank(rank),
    m_should_reboot(should_reboot)
{
    // Set buffer data
    Allocate_Buffer();
}


/**
 * @brief Destructor
 */
Segfault_Message::~Segfault_Message()
{
    Free_Buffer();
}


/**
 * @brief Allocate Buffer
 */
void Segfault_Message::Allocate_Buffer()
{
    // Get message size
    m_buffer = new char[Get_Buffer_Size_Bytes()];
    
    // Set message ID
    m_buffer[0] = Get_Message_ID();

    // Assign data
    Copy_Data_To_Buffer();

}

/**
 * Free Buffer
 */
void Segfault_Message::Free_Buffer()
{
    if( m_buffer != NULL && m_buffer != nullptr )
    {
        delete [] m_buffer;
        m_buffer = nullptr;
    }
}


/**
 * Get Buffer Data
 */
char* Segfault_Message::Get_Buffer_Data(){
    return m_buffer;
}

/**
 * Set Buffer Data
 */
void Segfault_Message::Set_Buffer_Data( const char* buffer ){

    // Copy Data
    for( int i=0; i<Get_Buffer_Size_Bytes(); i++ ){
        m_buffer[i] = buffer[i];
    }

    // Copy to data
    Copy_Buffer_To_Data();

}


/**
 * Copy Data to Buffer
 */
void Segfault_Message::Copy_Data_To_Buffer(){

    // Create Union
    union{
        int  ival[2];
        char cval[16];
    } converter;

    // Set data
    converter.ival[0] = m_rank;
    converter.ival[1] = m_should_reboot;

    // Create offset
    int offset = 1;

    // Iterate over buffer
    for( int i=0; i<16; i++ ){
        m_buffer[offset+i] = converter.cval[i];
    }


}


/**
 * Copy Buffer to Data
 */
void Segfault_Message::Copy_Buffer_To_Data()
{

    // Create Union
    union{
        int  ival[2];
        char cval[16];
    } converter;

    // Define our offset
    int offset = 1;

    // Copy Data
    for( int i=0; i<16; i++ )
    {
        converter.cval[i] = m_buffer[offset+i];
    }
    m_rank = converter.ival[0];
    m_should_reboot = converter.ival[1];

}



/**
 * Segfault Handler
 */
void Segmentation_Fault_Handler( int seg )
{

    // Print Output
    std::cout << "Segmentation Fault Detected in " << get_process_name_by_pid(getpid()) << std::endl;

    // Check if MPI Initialized
    int mpi_initialized;
    MPI_Initialized( &mpi_initialized );

    if( mpi_initialized == true ){
        
        
        // Get the hostname
        char system_name[256];
        int name_len;
        MPI_Get_processor_name( system_name, &name_len );

        // Get our rank
        int mpi_rank;
        MPI_Comm_rank( MPI_COMM_WORLD, &mpi_rank );

        // Find Communicator to Send Response to
        MPI_Comm comm = MPI_COMM_WORLD;
        MPI_Comm parent_comm;
        MPI_Comm_get_parent( &parent_comm );
        if( parent_comm != MPI_COMM_NULL ){
            comm = parent_comm;
        }

        // Send Message
        Segfault_Message segfault_message(mpi_rank, true);

        MPI_Send( segfault_message.Get_Buffer_Data(),
                  segfault_message.Get_Buffer_Size_Bytes(),
                  MPI_CHAR,
                  0, 
                  0, 
                  comm );

        std::cout << "Segmentation Fault Message Sent to Main Application Successfully." << std::endl;
        MPI_Finalize();
        std::exit(0);
    }
    
    // Exit
    std::exit(1);
}



/**
 * Internal Thread Entry Function
 */
void* MPI_Message_Receiver::InternalThreadEntryFunc( void* This )
{
    // Start Listener
    ((MPI_Message_Receiver*)This)->Start();

    //Exit Successfully
    return NULL;
}


/**
 * Constructor
 */
MPI_Message_Receiver::MPI_Message_Receiver( MPI_Comm const& comm )
  : m_is_running(false),
    m_mpi_comm(comm),
    m_running_mutex(PTHREAD_MUTEX_INITIALIZER)
{
    
    // Get our rank
    MPI_Comm_rank( m_mpi_comm, &m_my_rank);
    
    // Get the world size
    MPI_Comm_size( m_mpi_comm, &m_my_size );

}



/**
 * Start Receiving
 */
void MPI_Message_Receiver::Start(){
    
    // Misc Variables
    int errcode;
    MPI_Status status;
    char* message_data;
    int message_size;
    int message_ready = false;

    // Start running flag
    m_is_running = true;
    
    pthread_mutex_lock(&m_running_mutex);

    MPI_Message_Base::ptr_t message;

    // while running
    while( m_is_running )
    {

        // Probe for a message
        message_ready = false;
        while( m_is_running == true && message_ready == false ){
            errcode = MPI_Iprobe( MPI_ANY_SOURCE, MPI_ANY_TAG, m_mpi_comm, &message_ready, &status );
            if( errcode != MPI_SUCCESS ){
                std::cout << "MPI Error Code: " << errcode << std::endl;
                std::exit(1);
            }
        }
        if( m_is_running == false ){
            break;
        }

        // Get the message size
        MPI_Get_count( &status, MPI_CHAR, &message_size );


        // Create output buffer
        message_data = new char[message_size];

        // Receive Buffer
        MPI_Irecv( message_data, message_size, MPI_CHAR, status.MPI_SOURCE, status.MPI_TAG, m_mpi_comm, &m_mpi_request );
        
        // Test
        MPI_Wait( &m_mpi_request, &status );
        
        // Processing Buffer
        if( message_data[0] == 0 ){
            m_is_running = false;
        }

        // Handle
        if( message_data[0] == 1 ){
            // Create message
            message = Segfault_Message::ptr_t(new Segfault_Message());
            message->Set_Buffer_Data( message_data );
        }

        for( int i=0; i<m_message_handlers.size(); i++ ){
            m_message_handlers[i]->Process_Message( message );
        }

        // Delete buffer
        delete [] message_data;
    }

    // Exit Receiver
    pthread_mutex_unlock(&m_running_mutex);

}

/**
 * Stop 
 */
void MPI_Message_Receiver::Stop_Receiver()
{
    // Close Comms Message
    char CLOSE_COMMS_MESSAGE[1];
    CLOSE_COMMS_MESSAGE[0] = 0;

    MPI_Comm_size( m_mpi_comm, &m_my_size );
    MPI_Status status;
    int completed;

    // Only do if running
    if( m_is_running ){
        
    
        // Send message to stop
        MPI_Request_get_status( m_mpi_request, &completed, MPI_STATUS_IGNORE );

        if( completed == false ){
        
            // Cancel the requrest
            MPI_Cancel(&m_mpi_request );
        
            // Wait
            MPI_Wait( &m_mpi_request, &status );
        }


        // Command system to break
        m_is_running = false;
    }

    pthread_mutex_unlock(&m_running_mutex);
    pthread_join( m_receiving_thread, NULL );
}


