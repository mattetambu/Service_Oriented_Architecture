//Class Get_list

#ifndef Get_list_H_
#define Get_list_H_

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

#include "../Library/Interface.h"
#include "../Library/Socket_io.h"
#include "../Library/Types.h"
#include "../Library/Service.h"
#include "../Library/Files_manager.h"

#define IMAGES_STORAGE_DIRECTORY "./Files/Servers/Image_storage_server/"	
	

class Get_list : public Service{
	string path;
	
	public:

	Get_list ();
	Get_list (string name, string address, string port);
	Get_list (string name, string address, string port, string path);
	Get_list (Service_description* s_description);
	Get_list (Service_description* s_description, string path);
	virtual ~Get_list ();
		
	void inizialize_parameters (string path);
			
	bool execute ();
};

#endif
