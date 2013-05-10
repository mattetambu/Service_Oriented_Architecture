#ifndef Image_manipulation_server_functions_H_
#define Image_manipulation_server_functions_H_ 

	#include "../SOA_Library/Interface.h"
	#include "../SOA_Library/Threads.h"
	#include "./Horizontal_flip_image.h"
	#include "./Rotate_image.h"
	
	#define REQUEST_NOT_ACCEPTED 0
	#define N_THREADS 5

	Rotate_image* rotate_image;
	Horizontal_flip_image* horizontal_flip_image;
	Threads thread[N_THREADS], control_thread;
	string SP_address, SR_address, SP_port, SR_port;
	int listen_socket;


	bool check_server_arguments (int n_args, char** args) { // Checking arguments
		if (n_args < 2) {
			cout << "#SERVER > Set Image_Manipulation Server port [1024-65535]: ";
			cin >> SP_port;
		}
		else SP_port = args[1];
		if (atoi(SP_port.c_str()) < 1023 ||  atoi(SP_port.c_str()) > 65535 ) return false;
		
		if (n_args < 3) {
			cout << "#SERVER > Set Service_Register address: ";
			cin >> SR_address;
		}
		else SR_address = args[2];
		if (!check_address (SR_address)) return false;
		
		if (n_args < 4) {
			cout << "#SERVER > Set Service_Register port [1024-65535]: ";
			cin >> SR_port;
		}
		else SR_port = args[3];
		if (atoi(SR_port.c_str()) < 1023 ||  atoi(SR_port.c_str()) > 65535 ) return false;
		
		SP_address = get_my_ip();
		cout << "#SERVER > Image_Manipulation Server running on  " << SP_address << ":" << SP_port << endl;
		return true;
	}

	bool Image_manipulation_server_help () {
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
		cout << SPACER << SPACER << "rotate_image" << endl;
		cout << SPACER << SPACER << "horizontal_flip_image" << endl;
		
		return true;
	}

	void *thread_body (void* thread_ID) {
		int ID = (int) thread_ID;
			
		while (thread[ID].is_active()) {
			thread[ID].wait_start();
			if (!thread[ID].is_active()) break;
			cout << endl << "#SERVER > Client connetted" << endl;
			
			string service = receive_string(thread[ID].get_socket());
			cout << "#SERVER > Service request: " << service << endl;
			
			if (service == "rotate_image") {
				rotate_image->receive_service_request(thread[ID].get_socket());
				rotate_image->execute();
				rotate_image->send_service_responce(thread[ID].get_socket());
				
				cout << "#SERVER > Request for service rotate_image served" << endl;
			}
			else if (service == "horizontal_flip_image") {
				horizontal_flip_image->receive_service_request(thread[ID].get_socket());
				horizontal_flip_image->execute();
				horizontal_flip_image->send_service_responce(thread[ID].get_socket());
				
				cout << "#SERVER > Request for service horizontal_flip_image served" << endl;
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
				if (operand == "rotate_image") result = register_service (rotate_image);
				else if (operand == "horizontal_flip_image") result = register_service (horizontal_flip_image);
				else cout << "#SERVER > Can't register the service - Service " << operand.c_str() << " unknown" << endl;
			}
			else if (command == "unregister_service") {
				if (operand == "rotate_image") result = unregister_service (rotate_image->get_description());
				else if (operand == "horizontal_flip_image") result = unregister_service (horizontal_flip_image->get_description());
				else cout << "#SERVER > Can't unregister the service - Service " << operand.c_str() << " unknown" << endl;
			}
			else if (command == "help" && operand == "") result = Image_manipulation_server_help ();
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