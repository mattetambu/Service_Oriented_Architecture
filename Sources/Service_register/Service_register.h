//Class Service_register

#ifndef Service_register_H_
#define Service_register_H_

	#include "../SOA_Library/Types.h"

	#include <map>
	#include <list>
	#include <utility>


	class Service_register {
		private:
			map <string, list<Service_description*> > service_register;
			pthread_mutex_t mutex_1, mutex_2;
			int readers_count;

			void readers_prologue();
			void readers_epilogue();
			void writers_prologue();
			void writers_epilogue();
			
		public:
			Service_register();
			~Service_register();
			
			bool add_service_provider (string address, string port);
			bool remove_service_provider (string address, string port);
			
			bool add_service (string name, Service_description* s_description);
			bool remove_service (string name, string address, string port);
			
			Service_description* get_service (string required_service_name);
			bool find_service (string name, string address, string port);
			bool print_register();
	};

#endif
