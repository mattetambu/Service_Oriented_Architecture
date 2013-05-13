#ifndef Image_storage_server_functions_H_
#define Image_storage_server_functions_H_ 

	#include "../../SOA_Library/Interface.h"
	#include "../../SOA_Library/Threads.h"
	#include "./Store_image.h"
	#include "./Get_image.h"
	#include "./Get_list.h"
	
	#define IMAGES_STORAGE_DIRECTORY "./Work_directories/Servers/Image_storage_server/"	
	#define REQUEST_NOT_ACCEPTED 0
	#define N_THREADS 5
	#define BACKLOG_QUEUE 5

	Store_image* store_image;
	Get_image* get_image;
	Get_list* get_list;
	
	Threads thread[N_THREADS], control_thread;
	pthread_mutex_t mutex_1, mutex_2, mutex_thread_free;
	pthread_cond_t cond_thread_free;

	string SP_address, SR_address, SP_port, SR_port;
	int listen_socket, readers_count = 0;

	
	bool check_server_arguments (int n_args, char** args) { // Checking arguments
		if (n_args < 2) {
			cout << "#SERVER > Set Image_storage_server port [1024-65535]: ";
			getline(cin, SP_port);
		}
		else SP_port = args[1];
		if (atoi(SP_port.c_str()) < 1023 ||  atoi(SP_port.c_str()) > 65535 ) return false;
		
		if (n_args < 3) {
			cout << "#SERVER > Set Service_register_server address: ";
			getline(cin, SR_address);
		}
		else SR_address = args[2];
		if (!check_address (SR_address)) return false;
		
		if (n_args < 4) {
			cout << "#SERVER > Set Service_register_server port [1024-65535]: ";
			getline(cin, SR_port);
		}
		else SR_port = args[3];
		if (atoi(SR_port.c_str()) < 1023 ||  atoi(SR_port.c_str()) > 65535 ) return false;
		
		SP_address = get_my_ip();
		cout << "#SERVER > Image_storage_server running on  " << SP_address << ":" << SP_port << endl;
		return true;
	}

	void readers_prologue() {
		pthread_mutex_lock (&mutex_1);
		if (++readers_count == 1) pthread_mutex_lock (&mutex_2);
		pthread_mutex_unlock (&mutex_1);	
	}
	void readers_epilogue() {
		pthread_mutex_lock (&mutex_1);
		if (--readers_count == 0) pthread_mutex_unlock (&mutex_2);
		pthread_mutex_unlock (&mutex_1);	
	}
	void writers_prologue() {
		pthread_mutex_lock (&mutex_2);
	}
	void writers_epilogue() {
		pthread_mutex_unlock (&mutex_2);
	}
	
	bool assign_execution_thread (int client_socket) {
		int i = 0;
		while (i < N_THREADS)
			if (thread[i].test_and_set_busy()) {
				thread[i].set_socket(client_socket);
				thread[i].thread_start();
				break;
			}
			else i++;
		
		return (i != N_THREADS);
	}
	
	bool Image_storage_server_help () {
		cout << SPACER << "Command format:" << endl;
		cout << SPACER << SPACER << "command [operand]" << endl;
		cout << SPACER << "Accepted command list:" << endl;
		cout << SPACER << SPACER << "register_server" << endl;
		cout << SPACER << SPACER << "unregister_server" << endl;
		cout << SPACER << SPACER << "register_service operand" << endl;
		cout << SPACER << SPACER << "unregister_service operand" << endl;
		cout << SPACER << SPACER << "help" << endl;
		cout << SPACER << SPACER << "quit" << endl;
		cout << SPACER << "Accepted operand list:" << endl;
		cout << SPACER << SPACER << "get_list" << endl;
		cout << SPACER << SPACER << "get_image" << endl;
		cout << SPACER << SPACER << "store_image" << endl;
		
		return true;
	}

	void *thread_body (void* thread_ID) {
		int ID = (int) thread_ID;

		while (thread[ID].is_active()) {
			pthread_cond_signal(&cond_thread_free);
			thread[ID].wait_start();
			if (!thread[ID].is_active()) break;
			
			cout << endl << "#SERVER > Client connetted" << endl;
			string service = receive_string(thread[ID].get_socket());
			cout << "#SERVER > Service request: " << service << endl;
			
			if (service == "store_image") {
				store_image->receive_service_request(thread[ID].get_socket());
				
				writers_prologue();
				store_image->execute();
				writers_epilogue();
				
				store_image->send_service_responce(thread[ID].get_socket());
				cout << "#SERVER > Request for service store_image served" << endl;
			}
			else if (service == "get_image") {
				get_image->receive_service_request(thread[ID].get_socket());
				
				readers_prologue();
				get_image->execute();
				readers_epilogue();
				
				get_image->send_service_responce(thread[ID].get_socket());
				cout << "#SERVER > Request for service get_image served" << endl;
			}
			else if (service == "get_list") {
				get_list->receive_service_request(thread[ID].get_socket());
				
				readers_prologue();
				get_list->execute();
				readers_epilogue();
				
				get_list->send_service_responce(thread[ID].get_socket());
				cout << "#SERVER > Request for service get_list served" << endl;
			}
			else {
				send_int (thread[ID].get_socket(), (int) REQUEST_NOT_ACCEPTED);	// REQUEST NOT ACCEPTED
				cout << "#SERVER > Can't serve the request - Service " << service << " unknown" << endl;
			}
			
			close(thread[ID].get_socket());
			thread[ID].set_free();
		}
		return 0;
	}

	void *control_thread_body (void*) {
		while (control_thread.is_active()) {
			bool result = false;
			string activate, command = "", operand = "";
			getline(cin, activate);
			
			cout << "#SERVER > (Insert a command) ";
			getline(cin, command);
			operand = (command.find(' ') == string::npos)? "" : command.substr(command.find(' ')+1);
			command = command.substr(0, command.find_first_of(' '));
			
			if (command == "register_server" && operand == "") result = register_service_provider (SP_address, SP_port);
			else if (command == "unregister_server" && operand == "") result = unregister_service_provider (SP_address, SP_port);
			else if (command == "register_service") {
				if (operand == "get_image") result = register_service (get_image);
				else if (operand == "store_image") result = register_service (store_image);
				else if (operand == "get_list") result = register_service (get_list);
				else cout << "#SERVER > Can't register the service - Service " << operand.c_str() << " unknown" << endl;
			}
			else if (command == "unregister_service") {
				if (operand == "get_image") result = unregister_service (get_image->get_description());
				else if (operand == "store_image") result = unregister_service (store_image->get_description());
				else if (operand == "get_list") result = unregister_service (get_list->get_description());
				else cout << "#SERVER > Can't unregister the service - Service " << operand.c_str() << " unknown" << endl;
			}
			else if (command == "help" && operand == "") result = Image_storage_server_help ();
			else if (command == "quit" && operand == "") {
				control_thread.thread_exit();
				shutdown(listen_socket, SHUT_RDWR);
				result = true;
			}
			else {
				cout << "#SERVER > Can't execute the command - Command unknown" << endl;
				continue;
			}
			
			if (result) cout << "#SERVER > Command executed" << endl;
			else cout << "#SERVER > Command not executed" << endl;
		}
		return 0;
	}


#endif