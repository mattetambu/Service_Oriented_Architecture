#include "Socket_io.h"

	
	bool socket_initialization_client (int* client_socket, string address, string port) { // Client socket initialization
		sockaddr_in server_address;
		memset (&server_address, 0, sizeof (server_address));
		
		server_address.sin_family = AF_INET;
		server_address.sin_port = htons(atoi(port.c_str()));	
		if(inet_pton (AF_INET, (const char*)address.c_str(), &server_address.sin_addr) == 0) return false;
		
		*client_socket = socket(PF_INET, SOCK_STREAM, 0);
		if (*client_socket == -1 ||
			connect (*client_socket, (sockaddr*) &server_address, sizeof (server_address)) == -1) {
			//cerr << "\t\t ERROR - Server unreachable" << endl;
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
		if (*listen_socket == -1 ||
			bind (*listen_socket, (sockaddr *) &server_address, sizeof(server_address)) == -1 ||
			listen(*listen_socket, backlog_queue_length) == -1) return false;
		
		return true;
	}
	
	int accept_client_connection (int listen_socket) {
		int client_address_lenght;
		sockaddr_in client_address;
			
		client_address_lenght = sizeof(client_address);
		memset (&client_address, 0, client_address_lenght);
		return accept (listen_socket, (sockaddr *) &client_address, (socklen_t*) &client_address_lenght);
	}
	
	bool check_address (string address) {
		sockaddr_in server_address;
		memset (&server_address, 0, sizeof (server_address));

		return inet_pton (AF_INET, (const char*) address.c_str(), &server_address.sin_addr);
	}
	
	string get_my_ip () {
		int i = 0;
		char host_name [100];
		string address;
		hostent* host_ip;
		in_addr network_address;

		gethostname(host_name, sizeof(host_name));
		host_ip = gethostbyname(host_name);

		//for (i = 0; host_ip->h_addr_list[i+1] != 0; i++);
		memcpy (&network_address, host_ip->h_addr_list[i], sizeof(in_addr));
		address = inet_ntoa (network_address);
		
		return address;
	}
	
	
	bool send_int (int socket, int data) {
		int sent = send (socket, &data, sizeof(data), 0);
		if (sent == -1 || sent < (int) sizeof(data)) {
			cerr << "\t\t ERROR - Can't send an integer" << endl;
			return false;
		}
		return true;	
	}
	
	bool send_double (int socket, double data) {
		int sent = send (socket, &data, sizeof(data), 0);
		if (sent == -1 || sent < (int) sizeof(data)) {
			cerr << "\t\t ERROR - Can't send a double" << endl;
			return false;
		}
		return true;
	}
	
	bool send_string (int socket, string data) {
		int sent_number, size = data.size();
		if (!send_int (socket, size)) return false;
		
		sent_number = send (socket, data.c_str(), size, MSG_WAITALL);
		if (sent_number == -1 || sent_number < size) {
			cerr << "\t\t ERROR - Can't send a string" << endl;
			return false;
		}
		return true;
	}
	
	bool send_buffer (int socket, buffer* data) {
		int sent_number, size = data->size;
		if (!send_int (socket, size)) return false;
		
		sent_number = send (socket, data->pointer, size, MSG_WAITALL);
		if (sent_number == -1 || sent_number < size) {
			cerr << "\t\t ERROR - Can't send a buffer" <<endl;
			return false;
		}
		return true;
	}

	bool send_service_description (int socket, Service_description* s_description) {
		if (s_description == NULL) {
			send_string (socket, "");
			return false;
		}
		if (!send_string (socket, s_description->name) ||
			!send_string (socket, s_description->address) ||
			!send_string (socket, s_description->port) ||
			!send_int (socket, s_description->p_description.size())) return false;
		
		for(int i = 0; i < (int) s_description->p_description.size(); i++)
			if (!send_int (socket, (int) s_description->p_description[i].direction) ||
				!send_int (socket, (int) s_description->p_description[i].type)) return false;
		
		return true;
	}

	
	int receive_int (int socket) {
		int data, received = recv (socket, &data, sizeof(data), 0);
		if (received == -1 || received < (int) sizeof(data)) {
			cerr << "\t\t ERROR - Can't receive an integer" << endl;
			return -1;
		}
		return data;
	}
	
	string receive_string (int socket) {
		int size = receive_int (socket);
		if (size == -1) return "";
		
		char* received_string = new char [size+1];
		memset(received_string, '\0', size+1);
		int received = recv (socket, received_string, size, MSG_WAITALL);
		if (received == -1 || received < size) {
			cerr << "\t\t ERROR - Can't receive a string" << endl;
			return "";
		}
		received_string[size] = '\0';
		
		/*string return_string (received_string);
		delete received_string;
		return return_string;*/
		return string(received_string);
	}
	
	double receive_double (int socket) {
		double data;
		int received = recv (socket, &data, sizeof(data), 0);
		if (received == -1 || received < (int) sizeof(data)) {
			cerr << "\t\t ERROR - Can't receive a double" << endl;
			return -1;
		}
		return data;
	}
	
	buffer* receive_buffer (int socket) {
		buffer* data = new buffer;
		if ((data->size = receive_int (socket)) == -1) return NULL;
		data->pointer = (void*) malloc (data->size); 
		
		int received = recv (socket, data->pointer, data->size, MSG_WAITALL);
		if (received == -1 || received < data->size) {
			cerr << "\t\t ERROR - Can't receive a buffer" << endl;
			return NULL;
		}
		return data;
	}

	Service_description* receive_service_description (int socket) {
		int parameters_size;
		Service_description* s_description = new Service_description;
		
		if ((s_description->name = receive_string (socket)) == "" ||
			(s_description->address = receive_string (socket)) == "" ||
			(s_description->port = receive_string (socket)) == "" ||		
			(parameters_size = receive_int (socket)) == -1) return NULL;
			
		s_description->p_description.resize (parameters_size);
		for(int i = 0; i < parameters_size; i++)
			if ((s_description->p_description[i].direction = (Direction) receive_int (socket)) == -1 ||
				(s_description->p_description[i].type = (Type) receive_int (socket)) == -1) return NULL;
		
		return s_description;
	}
