//Class Rotate_image

#include "Rotate_image.h"

	Rotate_image::Rotate_image () {
		s_description.name = "rotate_image";
		path = string(ROTATE_IMAGE_DIRECTORY);
		inizialize_parameters (path);
	}
	Rotate_image::Rotate_image (string name, string address, string port) : Service (name, address, port) {
		path = string(ROTATE_IMAGE_DIRECTORY);
		inizialize_parameters (path);
	}
	Rotate_image::Rotate_image (string name, string address, string port, string path) : Service (name, address, port) {
		(*this).path = path;
		inizialize_parameters (path);
	}
	Rotate_image::Rotate_image (Service_description* s_description) : Service (s_description) {
		path = string(ROTATE_IMAGE_DIRECTORY);
		inizialize_parameters (path);
	}
	Rotate_image::Rotate_image (Service_description* s_description, string path) : Service (s_description) {
		(*this).path = path;
		inizialize_parameters (path);
	}
	
	Rotate_image::~Rotate_image () {}

	void Rotate_image::inizialize_parameters (string path) {
		add_parameter (IN, Integer);
		add_parameter (IN, Buffer);
		add_parameter(OUT, Buffer);
		
		string command = "mkdir -p " + path;
		if (system(command.c_str())) cerr << "ERROR - Can't create the service directory" << endl;
	}

	bool Rotate_image::execute ()  {	// TO BE IMPLEMENTED
		if (!responce.set_parameter(0, &parameters[1])) return false;
		return true;
	}
