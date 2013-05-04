#ifndef Socket_io_H_
#define Socket_io_H_

#include "Types.h"

#include <sys/types.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <string>
#include <string.h>
#include <sstream>

using namespace std;

	bool socket_initialization_client (int* client_socket, string address, string port);
	bool socket_initialization_server (int* listen_socket, string port, int backlog_queue_length);
	string get_my_ip ();
	
	bool send_int (int socket, int data);
	bool send_double (int socket, double data);
	bool send_string (int socket, string data);
	bool send_buffer (int socket, buffer* data);
	bool send_service_description (int socket, Service_description* s_description);

	int receive_int (int socket);
	string receive_string (int socket);
	double receive_double (int socket);
	buffer* receive_buffer (int socket);
	Service_description* receive_service_description (int socket);
	
#endif