//Class Horizontal_flip_image

#include "Horizontal_flip_image.h"

	Horizontal_flip_image::Horizontal_flip_image () {
		s_description.name = "horizontal_flip_image";
		path = string(FLIP_IMAGE_DIRECTORY);
		inizialize_parameters (path);
	}
	Horizontal_flip_image::Horizontal_flip_image (string name, string address, string port) : Service (name, address, port) {
		path = string(FLIP_IMAGE_DIRECTORY);
		inizialize_parameters (path);
	}
	Horizontal_flip_image::Horizontal_flip_image (string name, string address, string port, string path) : Service (name, address, port) {
		(*this).path = path;
		inizialize_parameters (path);
	}
	Horizontal_flip_image::Horizontal_flip_image (Service_description* s_description) : Service (s_description) {
		path = string(FLIP_IMAGE_DIRECTORY);
		inizialize_parameters (path);
	}
	Horizontal_flip_image::Horizontal_flip_image (Service_description* s_description, string path) : Service (s_description) {
		(*this).path = path;
		inizialize_parameters (path);
	}
	
	Horizontal_flip_image::~Horizontal_flip_image () {}

	void Horizontal_flip_image::inizialize_parameters (string path) {
		add_parameter (IN, Buffer);
		add_parameter (OUT, Buffer);
		
		string command = "mkdir -p " + path;
		if (system(command.c_str())) cerr << "ERROR - Can't create the service directory" << endl;
	}

	bool Horizontal_flip_image::execute () {	// TO BE IMPLEMENTED
		if (!responce.set_parameter(0, &parameters[0])) return false;
		return true;
	}
