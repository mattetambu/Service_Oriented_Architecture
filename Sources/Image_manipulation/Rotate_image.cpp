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
		add_parameter (OUT, Buffer);
		
		string command = "mkdir -p " + path;
		if (system(command.c_str())) cerr << "ERROR - Can't create the service directory" << endl;
	}

	bool Rotate_image::execute () {
		static int count = 0;
		stringstream image_count; image_count << count++;
		string source_path = path + "rotate_source_" + image_count.str() + ".jpg";
		string result_path = path + "rotated_" + image_count.str() + ".jpg";

		if (!make_image_from_buffer (source_path, &parameters[1].data.Buffer)) return false;
		
		Image result_image;
		result_image.magick("jpg");
		result_image.read(source_path);
		result_image.rotate(parameters[0].data.Integer % 360);
		result_image.write(result_path);
		
		Parameter *parameter = new Parameter;
		parameter->type = Buffer;
		if (!get_buffer_from_image (result_path, &parameter->data.Buffer)) return false;
		if (!responce.set_parameter(0, parameter)) return false;
		
		if (REMOVE_IMAGES && (remove(source_path.c_str()) || remove(result_path.c_str()))) cerr << "\t\tCan't remove temporany files" << endl;
		
		//free(parameter->data.Buffer.pointer);
		//delete parameter;
		return true;
	}
