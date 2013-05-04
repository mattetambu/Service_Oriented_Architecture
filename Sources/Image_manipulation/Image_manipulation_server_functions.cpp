#include "./Image_manipulation_server_functions.h"

extern Rotate_image* rotate_image;
extern Horizontal_flip_image* horizontal_flip_image;
extern Threads thread[N_THREADS], control_thread;
extern string SP_address, SR_address, SP_port, SR_port;

bool check_server_arguments (int n_args, char** args) { // Checking arguments
	sockaddr_in server_address;
	memset (&server_address, 0, sizeof (server_address));

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
	if (inet_pton (AF_INET, (const char*)SR_address.c_str(), &server_address.sin_addr) == 0) return false;
	
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
			// TO BE IMPLEMENTED
			cout << "#SERVER > Request unknown" << endl;
		}
		
		close(thread[ID].get_socket());
		thread[ID].set_free();
	}
	return 0;
}

/*void *control_thread_body (void* args) {
	//Service* horizontal_flip_image = new Horizontal_flip_image ("horizontal_flip_image", SP_address, SP_port);
	//Service* rotate_image = new Rotate_image ("rotate_image", SP_address, SP_port);
	bool result = false;
	
	while (control_thread.is_active()) {
		result = false;
		string command = "", operand = "";
		
		cout << "#SERVER > (Insert a command) ";
		getline(cin, command);
		operand = (command.find(' ') == string::npos)? "" : command.substr(command.find(' ')+1);
		command = command.substr(0, command.find_first_of(' '));
		
		if (command == "register_server" && operand == "") result = register_service_provider (SP_address, SP_port);
		else if (command == "unregister_server" && operand == "") result = unregister_service_provider (SP_address, SP_port);
		else if (command == "register_service") {
			if (operand == "rotate_image") result = register_service (rotate_image);
			else if (operand == "horizontal_flip_image") result = register_service (horizontal_flip_image);
			else cout << "#SERVER > Service " << operand.c_str() << " unknown";
		}
		else if (command == "unregister_service") {
			if (operand == "rotate_image") result = unregister_service (rotate_image->get_description());
			else if (operand == "horizontal_flip_image") result = unregister_service (horizontal_flip_image->get_description());
			else cout << "#SERVER > Service " << operand.c_str() << " unknown";
		}
		else if (command == "help" && operand == "") result = Image_manipulation_server_help ();
		else if (command == "quit" && operand == "") {
			unregister_service_provider (SP_address, SP_port);
			control_thread.thread_exit();
		}
		else {
			cout << "#SERVER > Unknown command" << endl;
			continue;
		}
		
		if (result) cout << "#SERVER > Command executed\n" << endl;
		else cout << "#SERVER > Command not executed\n" << endl;
		cout << endl;
	}
	return 0;
}*/
