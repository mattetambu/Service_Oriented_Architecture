//Class Get_image

#include "Get_image.h"

	Get_image::Get_image () {
		s_description.name = "get_image";
		path = string(IMAGES_STORAGE_DIRECTORY);
		inizialize_parameters (path);
	}
	Get_image::Get_image (string name, string address, string port) : Service (name, address, port) {
		path = string(IMAGES_STORAGE_DIRECTORY);
		inizialize_parameters (path);
	}
	Get_image::Get_image (string name, string address, string port, string path) : Service (name, address, port) {
		(*this).path = path;
		inizialize_parameters (path);
	}
	Get_image::Get_image (Service_description* s_description) : Service (s_description) {
		path = string(IMAGES_STORAGE_DIRECTORY);
		inizialize_parameters (path);
	}
	Get_image::Get_image (Service_description* s_description, string path) : Service (s_description) {
		(*this).path = path;
		inizialize_parameters (path);
	}
	
	Get_image::~Get_image () {}

	void Get_image::inizialize_parameters (string path) {
		add_parameter (IN, String);
		add_parameter (OUT, Buffer);
		
		string command = "mkdir -p " + path;
		if (system(command.c_str())) cerr << "ERROR - Can't create the service directory" << endl;
	}

	bool Get_image::execute () {
		string image_path = path + parameters[0].data.String;
		Parameter *parameter = new Parameter;
		parameter->type = Buffer;
		
		if (!get_buffer_from_image (image_path, &parameter->data.Buffer)) {
			parameter->data.Buffer.size = 0;
			parameter->data.Buffer.pointer = NULL;
			return false;
		}		
		responce.set_parameter(0, parameter);
		return true;
	}
