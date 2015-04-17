/**
 * @file    Spawn_Demo_Common.hpp
 * @author  Marvin Smith
 * @date    4/17/2015
 */
#ifndef __MPI_SPAWN_DEMO_COMMON_HPP__
#define __MPI_SPAWN_DEMO_COMMON_HPP__


// C++ Standard Libraries
#include <memory>
#include <pthread.h>
#include <vector>

// MPI Libraries
#include <mpi.h>


/**
 * Get a process name by pid.
 */
const char* get_process_name_by_pid(const int pid);

/**
 * Segfault Handler
 */
void Segmentation_Fault_Handler( int sig );


/**
 * @class MPI_Message_Base
 */
class MPI_Message_Base{

    public:
        
        /// Pointer Type
        typedef std::shared_ptr<MPI_Message_Base> ptr_t;

        /**
         * Get buffer data
         */
        virtual char* Get_Buffer_Data() = 0;


        /**
         * Set Buffer Data
         */
        virtual void Set_Buffer_Data( const char* buffer ) = 0;

        
        /**
         * @brief Get the Buffer Size
         */
        virtual int Get_Buffer_Size_Bytes()const = 0;

        
        /**
         * Get the Message ID
         */
        virtual char Get_Message_ID()const = 0;

}; /// End of MPI_Message_Base


/**
 * @class Segfault_Message
 */
class Segfault_Message : public MPI_Message_Base{

    public:
        
        /// Pointer Type
        typedef std::shared_ptr<Segfault_Message> ptr_t;

        /**
         * Constructor
         */
        Segfault_Message();


        /**
         * Constructor
         */
        Segfault_Message( const int& rank, 
                          const int& should_reboot );
        

        /**
         * @brief Destructor
         */
        ~Segfault_Message();

        /**
         * @brief Get Buffer Size in Bytes
         */
        inline virtual int Get_Buffer_Size_Bytes()const{
            return (sizeof(int)*2+1);
        }

        /**
         * @brief Get Buffer Data
         */
        virtual char* Get_Buffer_Data();


        /**
         * @brief Set Buffer Data
         */
        virtual void Set_Buffer_Data( const char* buffer );


        /**
         * @brief Get the rank
         *
         * @return Rank.
         */
        inline int Get_MPI_Rank()const{
            return m_rank;
        }

        /**
         * Check if we need to reboot
         */
        inline bool Should_Reboot()const{
            return (bool)m_should_reboot;
        }
        
        
        /**
         * Get the Message ID
         */
        inline virtual char Get_Message_ID()const{
            return 1;
        }

    
    private: 
 
        /**
         * @brief Allocate Buffer
         */
        void Allocate_Buffer();


        /**
         * @brief Free Buffer
         */
        void Free_Buffer();       


        /**
         * @brief Copy Buffer to Data
         */
        void Copy_Buffer_To_Data();

        /**
         * Copy Data to Buffer.
         */
        void Copy_Data_To_Buffer();


        // Rank
        int m_rank;

        // Should Reboot
        int m_should_reboot;

        // Buffer
        char* m_buffer;

}; /// End of Segfault_Message Class


/**
 * @class MPI_Message_Handler 
 */
class MPI_Message_Handler{

    public:
    
        /// Pointer Type
        typedef std::shared_ptr<MPI_Message_Handler> ptr_t;


        /**
         * Process Message
         */
        virtual void Process_Message( MPI_Message_Base::ptr_t message ) = 0;


}; // End of Message Receiver Handler Class


/**
 * @class MPI_Message_Receiver
 */
class MPI_Message_Receiver{

    public:
        
        /// Pointer Type
        typedef std::shared_ptr<MPI_Message_Receiver> ptr_t;
    
        
        /**
         * @brief Constructor
         */
        MPI_Message_Receiver( MPI_Comm const& comm );


        /**
         * @brief Add Message Handler
         */
        inline void Register_Message_Handler( MPI_Message_Handler::ptr_t handler )
        {
            m_message_handlers.push_back(handler);
        }
        
        /**
         * @brief Start Receiving
         */
        inline void Start_Receiver()
        {
            pthread_create(&m_receiving_thread, NULL, InternalThreadEntryFunc,this);
        }


        /**
         * @brief Stop Receiver
         */
        void Stop_Receiver();


    private:

        /**
         * @brief Internal Thread Function
         */
        static void* InternalThreadEntryFunc( void* This );

        /**
         * Start Receiving
         */
        void Start();

        /// Message Receivers
        std::vector<MPI_Message_Handler::ptr_t> m_message_handlers;

        /// Receiving Thread
        pthread_t m_receiving_thread;

        /// While Running
        bool m_is_running;

        /// MPI Communicator
        MPI_Comm m_mpi_comm;

        /// MPI Request
        MPI_Request m_mpi_request;

        /// Mutex
        pthread_mutex_t m_running_mutex;

        /// My Rank
        int m_my_rank;

        /// World Size
        int m_my_size;
        
}; // End of MPI_Message_Receiver



#endif
