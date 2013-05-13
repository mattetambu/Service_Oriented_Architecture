//Class Get_list

#include "Get_list.h"

	Get_list::Get_list () {
		s_description.name = "get_list";
		path = string(IMAGES_STORAGE_DIRECTORY);
		inizialize_parameters (path);
	}
	Get_list::Get_list (string name, string address, string port) : Service (name, address, port) {
		path = string(IMAGES_STORAGE_DIRECTORY);
		inizialize_parameters (path);
	}
	Get_list::Get_list (string name, string address, string port, string path) : Service (name, address, port) {
		(*this).path = path;
		inizialize_parameters (path);
	}
	Get_list::Get_list (Service_description* s_description) : Service (s_description) {
		path = string(IMAGES_STORAGE_DIRECTORY);
		inizialize_parameters (path);
	}
	Get_list::Get_list (Service_description* s_description, string path) : Service (s_description) {
		(*this).path = path;
		inizialize_parameters (path);
	}
	
	Get_list::~Get_list () {}

	void Get_list::inizialize_parameters (string path) {
		add_parameter(OUT, String);
		
		string command = "mkdir -p " + path;
		if (system(command.c_str())) cerr << "ERROR - Can't create the service directory" << endl;
	}

	bool Get_list::execute () {
		vector<string> server_image_list;
		Parameter *parameter = new Parameter;
		parameter->type = String;
		parameter->data.String = "";
		
		if (!make_file_list (path, &server_image_list)) return false;
		if ((int) server_image_list.size() > 0) {
			parameter->data.String = server_image_list[0];
			for (int i = 1; i < (int) server_image_list.size(); i++) parameter->data.String += "\n" + server_image_list[i];
		}
		
		if (!responce.set_parameter(0, parameter)) return false;
		
		delete parameter;
		return true;
	}
