//Class Store_image

#include "Store_image.h"

	Store_image::Store_image () {
		s_description.name = "store_image";
		inizialize_parameters (string(STORE_IMAGE_DIRECTORY));
	}
	Store_image::Store_image (string name, string address, string port) : Service (name, address, port) {
		inizialize_parameters (string(STORE_IMAGE_DIRECTORY));
	}
	Store_image::Store_image (string name, string address, string port, string path) : Service (name, address, port) {
		inizialize_parameters (path);
	}
	Store_image::Store_image (Service_description* s_description) : Service (s_description) {
		path = string(STORE_IMAGE_DIRECTORY);
		
		string command = "mkdir -p " + path;
		if (system(command.c_str())) cerr << "ERROR - Can't create the service directory" << endl;
	}
	Store_image::Store_image (Service_description* s_description, string path) : Service (s_description) {
		(*this).path = path;
		
		string command = "mkdir -p " + path;
		if (system(command.c_str())) cerr << "ERROR - Can't create the service directory" << endl;
	}
		
	Store_image::~Store_image () {}

	void Store_image::inizialize_parameters (string path) {
		(*this).path = path;
		add_parameter (IN, String);
		add_parameter (IN, Buffer);
				
		string command = "mkdir -p " + path;
		if (system(command.c_str())) cerr << "ERROR - Can't create the service directory" << endl;
	}

	bool Store_image::execute () {
		return make_image_from_buffer ((path + parameters[0].data.String), &parameters[1].data.Buffer);
	}
