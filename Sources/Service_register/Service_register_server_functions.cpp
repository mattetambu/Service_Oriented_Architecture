#include "./Service_register_server_functions.h"

extern Service_register* service_register;
extern Threads thread[N_THREADS], control_thread;
extern string SR_address, SR_port;
extern int listen_socket;

bool check_server_arguments (int n_args, char** args) { // Checking arguments
	sockaddr_in server_address;
	memset (&server_address, 0, sizeof (server_address));

	if (n_args < 2) {
		cout << "#SERVER > Set Service_Register Server port [1024-65535]: ";
		cin >> SR_port;
	}
	else SR_port = args[1];
	if (atoi(SR_port.c_str()) < 1023 ||  atoi(SR_port.c_str()) > 65535 ) return false;
	
	SR_address = get_my_ip();
	cout << "#SERVER > Service_Register Server running on  " << SR_address << ":" << SR_port << endl;
	return true;
}

bool Service_register_server_help () {
	return true;
}

void *thread_body (void* thread_ID) {
	int ID = ((int) thread_ID);
	bool service_result;
	string request, name, address, port;
	Service_description* s_description;
	
	while (thread[ID].is_active()) {
		thread[ID].wait_start();
		if (!thread[ID].is_active()) break;
		service_result = false;
		
		cout << "#SERVER > Client connetted" << endl;
		request = receive_string (thread[ID].get_socket());
		cout << "#SERVER > Service request: " << request << endl;
		
		if (request == "add_service_provider") {
			if (send_int (thread[ID].get_socket(), (int) REQUEST_ACCEPTED) && 
				(address = receive_string (thread[ID].get_socket())) != "" && 
				(port = receive_string (thread[ID].get_socket())) != "") {
					if (!(service_result = service_register->add_service_provider (address, port)))
						cout << "#SERVER > Server already registered" << endl;
					else cout << "#SERVER > Request for service add_service_provider served" << endl;
			}
		}
		else if (request == "remove_service_provider") {
			if (send_int (thread[ID].get_socket(), (int) REQUEST_ACCEPTED) && 
				(address = receive_string (thread[ID].get_socket())) != "" && 
				(port = receive_string (thread[ID].get_socket())) != "") {
					
					if (!(service_result = service_register->remove_service_provider (address, port)))
						cout << "#SERVER > Service provider not registered" << endl;
					else cout << "#SERVER > Request for service remove_service_provider served" << endl;
			}
		}
		else if (request == "add_service") {
			if (send_int (thread[ID].get_socket(), (int) REQUEST_ACCEPTED) && 
				(name = receive_string (thread[ID].get_socket())) != "" &&
				(s_description = receive_service_description (thread[ID].get_socket())) != NULL) {
					if (!(service_result = service_register->add_service(name, s_description)))
						cout << "#SERVER > Service " << name << " already registered" << endl;
					else cout << "#SERVER > Request for adding service " << name << " served" << endl;
			}
		}
		else if (request == "remove_service") {
			if (send_int (thread[ID].get_socket(), (int) REQUEST_ACCEPTED) && 
				(name = receive_string (thread[ID].get_socket())) != "" && 
				(address = receive_string (thread[ID].get_socket())) != "" && 
				(port = receive_string (thread[ID].get_socket())) != "") {
					if (!(service_result = service_register->remove_service(name, address, port)))
						cout << "#SERVER > Service " << name << " not registered" << endl;
					else cout << "#SERVER > Request for removing service " << name << " served" << endl;
			}
		}
		else if (request == "get_service") {
			if (send_int (thread[ID].get_socket(), (int) REQUEST_ACCEPTED) && 
				(name = receive_string (thread[ID].get_socket())) != "") {
					s_description = service_register->get_service(name);
					if (s_description == NULL) cout << "#SERVER > Service " << name << " not registered" << endl;
					if ((service_result = send_service_description (thread[ID].get_socket(), s_description)))
						cout << "#SERVER > Request for getting service " << name << " served" << endl;
			}
		}
		else send_int (thread[ID].get_socket(), (int) REQUEST_NOT_ACCEPTED);
		
		if (!service_result) cout << "#SERVER > Unable to serve the " << request << " request" << endl;
		close(thread[ID].get_socket());
		thread[ID].set_free();
	}
	return 0;
}


void *control_thread_body (void*) {
	while (control_thread.is_active()) {
		bool result = false;
		string command = "", operand = "";
		cin.get();
		
		cout << "#SERVER > (Insert a command) ";
		getline(cin, command);
		operand = (command.find(' ') == string::npos)? "" : command.substr(command.find(' ')+1);
		command = command.substr(0, command.find_first_of(' '));

		if (command == "help" && operand == "") result = Service_register_server_help ();
		else if (command == "print_register" && operand == "") result = service_register->print_register();
		else if (command == "quit" && operand == "") {
			control_thread.thread_exit();
			shutdown(listen_socket, SHUT_RDWR);
			result = true;
		}
		else {
			cout << "#SERVER >  Can't execute the command - Command unknown\n" << endl;
			continue;
		}
		
		if (result) cout << "#SERVER > Command executed\n" << endl;
		else cout << "#SERVER > Command not executed\n" << endl;
	}
	return 0;
}
