#include "./Image_storage_server_functions.h"

extern Store_image* store_image;
extern Get_image* get_image;
extern Get_list* get_list;
extern Threads thread[N_THREADS], control_thread;
extern pthread_mutex_t mutex_1, mutex_2;
extern string SP_address, SR_address, SP_port, SR_port;
extern int readers_count, listen_socket;


bool check_server_arguments (int n_args, char** args) { // Checking arguments
	sockaddr_in server_address;
	memset (&server_address, 0, sizeof (server_address));

	if (n_args < 2) {
		cout << "#SERVER > Set Image_Storage Server port [1024-65535]: ";
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
	cout << "#SERVER > Image_Storage Server running on  " << SP_address << ":" << SP_port << endl;
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
	
bool Image_storage_server_help () { // TO BE IMPLEMENTED
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
			cout << "#SERVER > Unable to serve the request - Service " << service << " unknown" << endl;
		}
		
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
		
		if (command == "register_server" && operand == "") result = register_service_provider (SP_address, SP_port);
		else if (command == "unregister_server" && operand == "") result = unregister_service_provider (SP_address, SP_port);
		else if (command == "register_service") {
			if (operand == "get_image") result = register_service (get_image);
			else if (operand == "store_image") result = register_service (store_image);
			else if (operand == "get_list") result = register_service (get_list);
			else cout << "#SERVER > Can't register the service - Service " << operand.c_str() << " unknown\n" << endl;
		}
		else if (command == "unregister_service") {
			if (operand == "get_image") result = unregister_service (get_image->get_description());
			else if (operand == "store_image") result = unregister_service (store_image->get_description());
			else if (operand == "get_list") result = unregister_service (get_list->get_description());
			else cout << "#SERVER > Can't unregister the service - Service " << operand.c_str() << " unknown\n" << endl;
		}
		else if (command == "help" && operand == "") result = Image_storage_server_help ();
		else if (command == "quit" && operand == "") {
			control_thread.thread_exit();
			shutdown(listen_socket, SHUT_RDWR);
			result = true;
		}
		else {
			cout << "#SERVER > Can't execute the command - Command unknown\n" << endl;
			continue;
		}
		
		if (result) cout << "#SERVER > Command executed\n" << endl;
		else cout << "#SERVER > Command not executed\n" << endl;
	}
	return 0;
}
