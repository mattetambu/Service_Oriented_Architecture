#ifndef Interface_H_
#define Interface_H_

	#include "./Service.h"
	#include <dirent.h>


	extern string SR_address, SR_port;

	bool register_service_provider (string address, string port);
	bool unregister_service_provider (string address, string port);
	
	bool register_service (Service* service);
	bool unregister_service (Service_description* s_description);
	
	Service* service_request (string service);

#endif