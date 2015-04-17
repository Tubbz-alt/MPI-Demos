/**
 *  @file    spawn-demo.cpp
 *  @author  Marvin Smith
 *  @date    4/17/2015
 */

// C++ Standard Libraries
#include <iostream>
#include <signal.h>
#include <string>
#include <unistd.h>

// MPI Libraries
#include <mpi.h>

// Utilities
#include "../../common/String_Utilities.hpp"
#include "Spawn_Demo_Common.hpp"

using namespace std;

// Global Variables
char** temp_argv_1;
char** temp_argv_2;
char** segfault_argv;


// Misc Error Codes and MPI Variables
int child_segfault_errcode;
MPI_Comm child_segfault_intercomm;


// Application Name
const std::string application_name = "Main-Application";

/**
 * Reboot Handler
 */
class Segfault_Message_Handler : public MPI_Message_Handler
{
    
    public:

        /// Pointer Type
        typedef std::shared_ptr<Segfault_Message_Handler> ptr_t;

        /**
         * Process Message
         */
        virtual void Process_Message( MPI_Message_Base::ptr_t message )
        {
            
            // Cast to Segfault Message
            Segfault_Message::ptr_t segfault_msg = std::dynamic_pointer_cast<Segfault_Message>(message);
            
            // Get the Rank of the Process Which Failed
            int rank = segfault_msg->Get_MPI_Rank();

            // Check if we need to reboot
            bool request_reboot = segfault_msg->Should_Reboot();

            // If a reboot is requested, start the process
            if( request_reboot == true ){
               
                std::cout << application_name << " : Rebooting the segfault process" << std::endl;
                // Spawn the Segfault Child
                MPI_Comm_spawn( "./release/bin/child-segfault", 
                                segfault_argv,
                                1, 
                                MPI_INFO_NULL, 
                                0,
                                MPI_COMM_WORLD, 
                                &child_segfault_intercomm, 
                                &child_segfault_errcode );

            }

        }

}; // End of Segfault_Message_Handler



/**
 * Main Function
 */
int main( int argc, char* argv[] )
{

    // Register the Segfault Handler
    signal(SIGSEGV, Segmentation_Fault_Handler );

    // Initialize Arguments
    temp_argv_1 = new char*[2];
    temp_argv_2 = new char*[2];
    segfault_argv = new char*[2];
    temp_argv_1[0] = "1";
    temp_argv_1[1] = NULL;
    temp_argv_2[0] = "2";
    temp_argv_2[1] = NULL;
    segfault_argv[0] = "0";
    segfault_argv[1] = NULL;



    // Initialize MPI
    int mpi_thread_provided;
    int mpi_thread_required = MPI_THREAD_MULTIPLE;
    MPI_Init_thread( &argc, &argv, mpi_thread_required, &mpi_thread_provided );

    // Start of main
    std::cout << application_name << " : Starting Main Demo" << std::endl;

    
    // Spawn the Persistent Child
    int child_persistent_errcode;
    MPI_Comm child_persistent_intercomm;
    std::cout << application_name << " : Spawning Persistent-Child" << std::endl;
    MPI_Comm_spawn( "./release/bin/child-persistent", 
                    MPI_ARGV_NULL, 
                    1, 
                    MPI_INFO_NULL, 
                    0,
                    MPI_COMM_WORLD, 
                    &child_persistent_intercomm, 
                    &child_persistent_errcode );
    
    
    // Spawn 2 Temporary Children
    int child_temporary_errcode;
    MPI_Comm child_temporary_intercomm_01;
    MPI_Comm child_temporary_intercomm_02;


    std::cout << application_name << " : Spawning Temporary-Child" << std::endl;
    MPI_Comm_spawn( "./release/bin/child-temporary", 
                    temp_argv_1,
                    1, 
                    MPI_INFO_NULL,
                    0,
                    MPI_COMM_WORLD,
                    &child_temporary_intercomm_01, 
                    &child_temporary_errcode );
    
    // Wait for a bit 
    sleep(1);
    
    std::cout << application_name << " : Spawning Temporary-Child" << std::endl;
    MPI_Comm_spawn( "./release/bin/child-temporary", 
                    temp_argv_2,
                    1, 
                    MPI_INFO_NULL,
                    0,
                    MPI_COMM_WORLD,
                    &child_temporary_intercomm_02, 
                    &child_temporary_errcode );

    
    // Spawn the Segfault Child
    std::cout << application_name << " : Spawning Segfault-Child" << std::endl;
    MPI_Comm_spawn( "./release/bin/child-segfault", 
                    segfault_argv,
                    1, 
                    MPI_INFO_NULL, 
                    0,
                    MPI_COMM_WORLD, 
                    &child_segfault_intercomm, 
                    &child_segfault_errcode );

    // Update the segfault handler to allow it to reboot cleanly
    segfault_argv[0] = "1";
    
    // Create the Message Receiver
    MPI_Message_Receiver message_receiver(child_segfault_intercomm);
    
    // Register a Segfault Handler
    Segfault_Message_Handler::ptr_t segfault_message_handler(new Segfault_Message_Handler());
    message_receiver.Register_Message_Handler(segfault_message_handler);

    // Start Listening
    message_receiver.Start_Receiver();



    // Wait on Persistent Child Intercommunicator
    MPI_Barrier( child_persistent_intercomm );

    // Wait on Comm World
    std::cout << application_name << " : Waiting at Final Barrier" << std::endl;
    MPI_Barrier( MPI_COMM_WORLD );

    // Stop Receiver
    message_receiver.Stop_Receiver();

    // Finalize MPI
    MPI_Finalize();
    
    
    delete [] temp_argv_1;
    delete [] temp_argv_2;

    // End of Main Demo
    std::cout << application_name << " : End of Demo" << std::endl;

    return 0;
}


