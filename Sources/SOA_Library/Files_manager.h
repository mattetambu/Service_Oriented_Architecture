#ifndef Files_manager_H_
#define Files_manager_H_

	#include "Types.h"
	#include <dirent.h>
	#include <sys/stat.h>
	#include <sstream>


	string make_working_directory (string path);
	bool make_file_list (string path, vector<string> *file_list);
	bool make_image_from_buffer (string image_path, buffer* image_buffer);
	bool get_buffer_from_image (string image_path, buffer* image_buffer);
	
#endif