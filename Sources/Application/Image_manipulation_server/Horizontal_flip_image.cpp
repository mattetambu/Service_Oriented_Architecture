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

	bool Horizontal_flip_image::execute () {
		static int count = 0;
		stringstream image_count; image_count << count++;
		string source_path = path + "flip_source_" + image_count.str() + ".jpg";
		string result_path = path + "flipped_" + image_count.str() + ".jpg";

		if (!make_image_from_buffer (source_path, &parameters[0].data.Buffer)) return false;
		
		Image result_image;
		result_image.magick("jpg");		
		result_image.read(source_path);
		result_image.flop();
		result_image.write(result_path);
		
		Parameter *parameter = new Parameter;
		parameter->type = Buffer;
		if (!get_buffer_from_image (result_path, &parameter->data.Buffer)) return false;
		if (!responce.set_parameter(0, parameter)) return false;
		
		if (REMOVE_IMAGES && (remove(source_path.c_str()) || remove(result_path.c_str()))) cerr << "\t\tCan't remove temporany files" << endl;
		
		delete parameter;
		return true;
	}
