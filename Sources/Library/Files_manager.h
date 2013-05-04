#ifndef Files_manager_H_
#define Files_manager_H_

#include <dirent.h>
#include <sys/stat.h>
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

#include "../Library/Types.h"

using namespace std;

	bool make_file_list (string path, vector<string> *file_list);
	bool make_image_from_buffer (string image_path, buffer* image_buffer);
	bool get_buffer_from_image (string image_path, buffer* image_buffer);
	
#endif