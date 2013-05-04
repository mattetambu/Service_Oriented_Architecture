#include "Interface.h"

	/*bool set_register_address (const char* address, const char* port) {
		// TO BE IMPLEMENTED
		return true;	
	}*/

	bool register_service_provider (string address, string port) {
		int socket;
		if (!socket_initialization_client (&socket, SR_address, SR_port)) return false;
		
		if (!send_string (socket, "add_service_provider")) return false;
		if (!send_string (socket, address)) return false;
		if (!send_string (socket, port)) return false;
		
		close(socket);
		return true;
	}

	bool unregister_service_provider (string address, string port) {
		int socket;
		if (!socket_initialization_client (&socket, SR_address, SR_port)) return false;
		
		if (!send_string (socket, "remove_service_provider")) return false;
		if (!send_string (socket, address)) return false;
		if (!send_string (socket, port)) return false;
		
		close(socket);
		return true;
	}
	
	bool register_service (Service* service) {
		int socket;
		if (!socket_initialization_client (&socket, SR_address, SR_port)) return false;
		
		if (!send_string (socket, "add_service")) return false;
		if (!send_string (socket, service->get_name())) return false;
		if (!send_service_description(socket, service->get_description())) return false;
		
		close(socket);
		return true;
	}
	
	bool unregister_service (Service_description* s_description) {
		int socket;
		if (!socket_initialization_client (&socket, SR_address, SR_port)) return false;
		
		if (!send_string (socket, "remove_service")) return false;
		if (!send_string (socket, s_description->name)) return false;
		if (!send_string (socket, s_description->address)) return false;
		if (!send_string (socket, s_description->port)) return false;
		
		close(socket);
		return true;
	}
	
	
	Service* service_request (string service_name) {
		int socket;
		if (!socket_initialization_client (&socket, SR_address, SR_port)) return false;
		
		if (!send_string (socket, "get_service")) return false;
		if (!send_string (socket, service_name)) return false;

		Service_description* s_description = receive_service_description (socket);
		if (s_description == NULL) return NULL;
		
		close(socket);
		return new Service (s_description);
	}
	
	
	void print_service_description (Service_description* s_description) {  // TO BE REMOVED
		cout << "\n\n Printing service_description:" << endl;
		cout << "s_description->name:" << s_description->name << endl;
		cout << "s_description->address:" << s_description->address << endl;
		cout << "s_description->port:" << s_description->port << endl;
		
		cout << "s_description->p_description.size():" << s_description->p_description.size() << endl;
		cout << "Parameters description:" << endl;
		for(int i = 0; i < (int) s_description->p_description.size(); i++) {
			cout << SPACER << "s_description->p_description[" << i << "].direction:" << s_description->p_description[i].direction << endl;
			cout << SPACER << "s_description->p_description[" << i << "].type:" << s_description->p_description[i].type << endl;
		}
	}