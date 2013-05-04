#ifndef Clients_functions_H_
#define Clients_functions_H_ 

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
	#include "../Library/Files_manager.h"
	
	#define IMAGES_DIRECTORY "Images/"
	#define CLIENT_DIRECTORY "./Files/Clients/"
	
	using namespace std;
		
	bool check_client_arguments (int n_args, char** args);
	string choose_random_file(vector<string> folder_files);
	
#endif