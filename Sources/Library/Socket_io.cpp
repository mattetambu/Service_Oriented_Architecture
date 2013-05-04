#include "Socket_io.h"

	
	bool socket_initialization_client (int* client_socket, string address, string port) { // Client socket initialization
		sockaddr_in server_address;
		memset (&server_address, 0, sizeof (server_address));
		
		server_address.sin_family = AF_INET;
		server_address.sin_port = htons(atoi(port.c_str()));	
		if(inet_pton (AF_INET, (const char*)address.c_str(), &server_address.sin_addr) == 0) return false;
		
		*client_socket = socket(PF_INET, SOCK_STREAM, 0);
		
		if (*client_socket == -1) return false;
		if (connect (*client_socket, (sockaddr*) &server_address, sizeof (server_address)) == -1) {
			cerr << "\t\t ERROR - Server unreachable" << endl;
			return false;
		}

		return true;
	}
	
	bool socket_initialization_server (int* listen_socket, string port, int backlog_queue_length) { // Server socket initialization
		sockaddr_in server_address;
		memset (&server_address, 0, sizeof (server_address));
		
		server_address.sin_family = AF_INET;
		server_address.sin_port = htons(atoi(port.c_str()));	
		server_address.sin_addr.s_addr = htonl(INADDR_ANY);
		
		*listen_socket = socket(PF_INET, SOCK_STREAM, 0);
		if (*listen_socket == -1) return false;
		if (bind (*listen_socket, (sockaddr *) &server_address, sizeof(server_address)) == -1) return false;
		if (listen(*listen_socket, backlog_queue_length) == -1) return false;
		
		return true;
	}
	
	string get_my_ip () {
		char host_name [100];
		hostent* host_ip;
		in_addr network_address;
		string address;

		gethostname(host_name, sizeof(host_name));
		host_ip = gethostbyname(host_name);

		memcpy(&network_address, host_ip->h_addr_list[0], sizeof(in_addr));
		address = inet_ntoa (network_address);
		
		return address;
	}
	
	
	bool send_int (int socket, int data) {
		int sent = send (socket, &data, sizeof(data), 0);
		if (sent == -1 || sent < (int) sizeof(data)) {
			cout << "\t\t  ERROR - Unable to send an integer" << endl;
			return false;
		}
		return true;	
	}
	
	bool send_double (int socket, double data) {
		int sent = send (socket, &data, sizeof(data), 0);
		if (sent == -1 || sent < (int) sizeof(data)) {
			cout << "\t\t  ERROR - Unable to send a double" << endl;
			return false;
		}
		return true;
	}
	
	bool send_string (int socket, string data) {
		int sent_number, size = data.size();
		if (!send_int (socket, size)) return false;
		
		sent_number = send (socket, data.c_str(), size, MSG_WAITALL);
		if (sent_number == -1 || sent_number < size) {
			cout << "\t\t  ERROR - Unable to send a string" << endl;
			return false;
		}
		return true;
	}
	
	bool send_buffer (int socket, buffer* data) {
		int sent_number, size = data->size;
		if (!send_int (socket, size)) return false;
		
		sent_number = send (socket, data->pointer, size, MSG_WAITALL);
		if (sent_number == -1 || sent_number < size) {
			cout << "\t\t  ERROR - Unable to send a buffer" <<endl;
			return false;
		}
		return true;
	}

	bool send_service_description (int socket, Service_description* s_description) {
		if (!send_string (socket, s_description->name)) return false;
		if (!send_string (socket, s_description->address)) return false;
		if (!send_string (socket, s_description->port)) return false;
		
		if (!send_int (socket, s_description->p_description.size())) return false;
		for(int i = 0; i < (int) s_description->p_description.size(); i++) {
			if (!send_int (socket, (int) s_description->p_description[i].direction)) return false;
			if (!send_int (socket, (int) s_description->p_description[i].type)) return false;
		}
		
		return true;
	}

	
	int receive_int (int socket) {
		int data = 2000, received = recv (socket, &data, sizeof(data), 0);
		if (received == -1 || received < (int) sizeof(data)) {
			cout << "\t\t  ERROR - Unable to receive an integer" << endl;
			return -1;
		}
		return data;
	}
	
	string receive_string (int socket) {
		int size = receive_int (socket);
		if (size == -1) return NULL;
		
		char* received_string = (char*) malloc (size+1); 
		memset(received_string, '\0', size+1);
		int received = recv (socket, received_string, size, MSG_WAITALL);
		
		if (received == -1 || received < size) {
			cout << "\t\t  ERROR - Unable to receive a string" << endl;
			return NULL;
		}
		received_string[size] = '\0';
		return string(received_string);
	}
	
	double receive_double (int socket) {
		double data;
		int received = recv (socket, &data, sizeof(data), 0);
		if (received == -1 || received < (int) sizeof(data)) {
			cout << "\t\t  ERROR - Unable to receive a double" << endl;
			return -1;
		}
		return data;
	}
	
	buffer* receive_buffer (int socket) {
		buffer* data = new buffer;
		data->size = receive_int (socket);
		if (data->size == -1) return NULL;
		data->pointer = (void*) malloc (data->size); 
		
		int received = recv (socket, data->pointer, data->size, MSG_WAITALL);
		if (received == -1 || received < data->size) {
			cout << "\t\t  ERROR - Unable to receive a buffer" << endl;
			return NULL;
		}
		return data;
	}

	Service_description* receive_service_description (int socket) {
		Service_description* s_description = new Service_description();
		s_description->name = receive_string (socket);
		s_description->address = receive_string (socket);
		s_description->port = receive_string (socket);
		
		int parameters_size = receive_int (socket);
		s_description->p_description.resize (parameters_size);
			
		for(int i = 0; i < parameters_size; i++) {
			s_description->p_description[i].direction = (Direction) receive_int (socket);
			s_description->p_description[i].type = (Type) receive_int (socket);
		}

		close(socket);
		return s_description;
	}
