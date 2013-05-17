//Class Get_image

#include "Get_image.h"

	Get_image::Get_image () {
		s_description.name = "get_image";
		inizialize_parameters (string(GET_IMAGE_DIRECTORY));
	}
	Get_image::Get_image (string name, string address, string port) : Service (name, address, port) {
		inizialize_parameters (string(GET_IMAGE_DIRECTORY));
	}
	Get_image::Get_image (string name, string address, string port, string path) : Service (name, address, port) {
		inizialize_parameters (path);
	}
	Get_image::Get_image (Service_description* s_description) : Service (s_description) {
		path = string(GET_IMAGE_DIRECTORY);
		
		string command = "mkdir -p " + path;
		if (system(command.c_str())) cerr << "ERROR - Can't create the service directory" << endl;
	}
	Get_image::Get_image (Service_description* s_description, string path) : Service (s_description) {
		(*this).path = path;
		
		string command = "mkdir -p " + path;
		if (system(command.c_str())) cerr << "ERROR - Can't create the service directory" << endl;
	}
	
	Get_image::~Get_image () {}

	void Get_image::inizialize_parameters (string path) {
		(*this).path = path;
		add_parameter (IN, String);
		add_parameter (OUT, Buffer);
		
		string command = "mkdir -p " + path;
		if (system(command.c_str())) cerr << "ERROR - Can't create the service directory" << endl;
	}

	bool Get_image::execute () {
		string image_path = path + parameters[0].data.String;
		Parameter *parameter = new Parameter;
		parameter->type = Buffer;
		
		if (!get_buffer_from_image (image_path, &parameter->data.Buffer)) return false;		
		if (!responce.set_parameter(0, parameter)) return false;
		
		delete parameter;
		return true;
	}
