#ifndef Image_storage_server_functions_H_
#define Image_storage_server_functions_H_ 

	#include <stdio.h>
	#include <stdlib.h>
	#include <iostream>
	#include <vector>
	#include <string>
	#include <netinet/in.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <arpa/inet.h>
	#include <netdb.h>
	#include <sstream>
	#include <pthread.h>
	
	
	#include "./Store_image.h"
	#include "./Get_image.h"
	#include "./Get_list.h"
	#include "../Library/Interface.h"
	#include "../Library/Threads.h"
	#include "../Library/Socket_io.h"
	
	#define IMAGES_STORAGE_DIRECTORY "./Files/Servers/Image_storage_server/"	
	#define N_THREADS 5

	using namespace std;
	
	void *thread_body (void *identifier);
	void *control_thread_body (void *args);

	void readers_prologue();
	void readers_epilogue();
	void writers_prologue();
	void writers_epilogue();

	bool check_server_arguments (int n_args, char** args);
	bool Image_storage_server_help ();

#endif