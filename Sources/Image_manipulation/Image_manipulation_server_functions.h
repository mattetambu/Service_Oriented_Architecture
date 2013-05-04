#ifndef Image_manipulation_server_functions_H_
#define Image_manipulation_server_functions_H_ 

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
	
	#include "./Horizontal_flip_image.h"
	#include "./Rotate_image.h"
	#include "../Library/Interface.h"
	#include "../Library/Threads.h"
	#include "../Library/Socket_io.h"
	
	#define N_THREADS 5

	using namespace std;
	
	void *thread_body (void *identifier);
	void *control_thread_body (void *args);
	
	bool check_server_arguments (int n_args, char** args);
	bool Image_manipulation_server_help ();

#endif