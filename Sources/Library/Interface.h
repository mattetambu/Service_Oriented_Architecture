#ifndef Interface_H_
#define Interface_H_

#include "Service.h"
#include "Responce.h"
#include "Socket_io.h"

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <vector>
#include <string>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sstream>
#include <pthread.h>

using namespace std;

extern string SR_address, SR_port;

	bool set_register_address (const char* address, const char* port);
		
	bool register_service_provider (string address, string port);
	bool unregister_service_provider (string address, string port);
	
	bool register_service (Service* service);
	bool unregister_service (Service_description* s_description);
	
	Service* service_request (string service);

	void print_service_description (Service_description* s_description); // TO BE REMOVED

#endif