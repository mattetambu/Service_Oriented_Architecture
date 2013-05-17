#include "Interface.h"


	bool register_service_provider (string address, string port) {
		int socket;
		bool result = false;
		if (!check_address (address) ||
			atoi(port.c_str()) < 1023 ||  atoi(port.c_str()) > 65535 ||
			!socket_initialization_client (&socket, SR_address, SR_port)) return false;
		
		if (send_string (socket, "add_service_provider") &&
			receive_int (socket) != -1 &&
			send_string (socket, address) &&
			send_string (socket, port)) result = true;
		
		close(socket);
		return result;
	}

	bool unregister_service_provider (string address, string port) {
		int socket;
		bool result = false;
		if (!check_address (address) ||
			atoi(port.c_str()) < 1023 ||  atoi(port.c_str()) > 65535 ||
			!socket_initialization_client (&socket, SR_address, SR_port)) return false;
		
		if (send_string (socket, "remove_service_provider") &&
			receive_int (socket) != -1 &&
			send_string (socket, address) &&
			send_string (socket, port)) result = true;
		
		close(socket);
		return result;
	}
	
	bool register_service (Service_description* s_description) {
		int socket;
		bool result = false;
		if (s_description == NULL ||
			!socket_initialization_client (&socket, SR_address, SR_port)) return false;
		
		if (send_string (socket, "add_service") &&
			receive_int (socket) != -1 &&
			send_service_description(socket, s_description)) result = true;
		
		close(socket);
		return result;
	}
	
	bool unregister_service (Service_description* s_description) {
		int socket;
		bool result = false;
		if (s_description == NULL ||
			!socket_initialization_client (&socket, SR_address, SR_port)) return false;
				
		if (send_string (socket, "remove_service") &&
			receive_int (socket) != -1 &&
			send_string (socket, s_description->name) &&
			send_string (socket, s_description->address) &&
			send_string (socket, s_description->port)) result = true;
		
		close(socket);
		return result;
	}
	
	
	Service* service_request (string service_name) {
		int socket;
		Service_description* s_description = NULL;
		if (service_name == "" ||
			!socket_initialization_client (&socket, SR_address, SR_port)) return NULL;
		
		if (send_string (socket, "get_service") &&
			receive_int (socket) != -1 &&
			send_string (socket, service_name)) s_description = receive_service_description (socket);
		
		close(socket);
		return (s_description == NULL) ? NULL : new Service (s_description);
	}
