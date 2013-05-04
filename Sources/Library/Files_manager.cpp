#include "Files_manager.h"

	
	bool make_file_list (string path, vector<string> *file_list) {
		DIR* directory = opendir(path.c_str());
		dirent* directory_info;
		struct stat file_info;
		
		if (!directory) {
			cerr << "#CLIENT > ERROR - Can't open the image_storage folder" << endl;
			return false;
		}
		while ((directory_info = readdir(directory))) {
			if (directory_info->d_name[0] == '.') continue;
			if (stat((path + directory_info->d_name).c_str(), &file_info)) continue;
			if (S_ISDIR(file_info.st_mode)) continue;
			
			(*file_list).push_back(directory_info->d_name);
		}
		
		return true;
	}
	
	bool make_image_from_buffer (string image_path, buffer* image_buffer) {
		if (image_buffer->size == 0) {
			cerr << "#SERVER > " SPACER << " ERROR - No image to store (image buffer is empty)" << endl;
			return false;
		}
		FILE* image = fopen (image_path.c_str(), "w");
		int result = fwrite (image_buffer->pointer, 1, image_buffer->size, image);
		if(result != image_buffer->size) {
			cerr << "#SERVER > " SPACER << " ERROR - Can't create the image " << image_path << " correctly" << endl;
			return false;
		}
		fclose(image);
		return true;	
	}
	
	bool get_buffer_from_image (string image_path, buffer* image_buffer) {
		struct stat file_info;
		stat(image_path.c_str(), &file_info);
		
		FILE* file = fopen(image_path.c_str(), "r");
		if(file == NULL) {
			cerr << "#CLIENT > " << SPACER << SPACER << " ERROR - Choosed file " << image_path << " not found" << endl;
			return false;
		}
		image_buffer->size = file_info.st_size;
		image_buffer->pointer = malloc(image_buffer->size);
		
		if(fread(image_buffer->pointer, 1, image_buffer->size, file) != (unsigned) image_buffer->size || image_buffer->size == 0) {
			cerr <<"#CLIENT > " << SPACER << SPACER << " ERROR - Cannot open correctly the image " << image_path << endl;
			free (image_buffer->pointer);
			return false;
		}
		fclose(file);
		return true;
	}