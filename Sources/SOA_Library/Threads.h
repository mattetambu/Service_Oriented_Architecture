//Class Threads

#ifndef Threads_H_
#define Threads_H_

	#include <pthread.h>

	
	class Threads {
		private:	
			bool busy;
			bool active;
			int client_socket;
			
			pthread_t thread_ID;
			pthread_mutex_t mutex;
			pthread_cond_t condition;	
			
		public:
			Threads();
			virtual ~Threads();
			
			bool test_and_set_busy();
			void set_busy();
			void set_free();
			void set_socket (int client_socket);
			void set_ID (pthread_t thread_ID);
			
			int get_socket ();
			pthread_t get_ID ();
			
			bool is_busy();
			bool is_active();
			
			void wait_start();
			void thread_start();
			void thread_exit();
	};

#endif