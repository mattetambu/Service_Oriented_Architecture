//Class Service

#include "Service.h"

	Service::Service (string name, string address, string port) {
		s_description.name = name;
		s_description.address = address;
		s_description.port = port;
	}
	
	Service::Service (Service_description* s_description) {
		(*this).s_description.name = s_description->name;
		(*this).s_description.address = s_description->address;
		(*this).s_description.port = s_description->port;
		
		for (int i = 0; i < (int) s_description->p_description.size(); i++)
			add_parameter (s_description->p_description[i].direction, s_description->p_description[i].type);
	}
	
	Service::~Service () {
		for (int i = 0; i < (int) parameters.size(); i++)
			if ((parameters[i].type == Buffer) && parameters[i].data.Buffer.size != 0) {
				free (parameters[i].data.Buffer.pointer);
				parameters[i].data.Buffer.size = 0;
			}
		parameters.clear();
	}

	
	void Service::add_parameter (Direction direction, Type type) {
		s_description.p_description.resize(s_description.p_description.size()+1);
		s_description.p_description.back().direction = direction;
		s_description.p_description.back().type = type;
		
		if (direction == OUT) responce.add_parameter (type);
		else {
			parameters.resize(parameters.size()+1);
			parameters.back().type = type;
			//if(parameters.back().type == Buffer) 
				parameters.back().data.Buffer.size = 0;
		}
	}
	
	bool Service::set_input_parameters(vector<Parameter> parameters) {
		if ((*this).parameters.size() != parameters.size()) return false;
		
		for(int i = 0; i < (int) parameters.size(); i++) {
			if ((*this).parameters[i].type != parameters[i].type) return false;
			if (parameters[i].type == Integer) (*this).parameters[i].data.Integer = parameters[i].data.Integer;
			else if (parameters[i].type == Double) (*this).parameters[i].data.Double = parameters[i].data.Double;
			else if (parameters[i].type == String) (*this).parameters[i].data.String = parameters[i].data.String;
			else {
				(*this).parameters[i].data.Buffer.size = parameters[i].data.Buffer.size;
				(*this).parameters[i].data.Buffer.pointer = parameters[i].data.Buffer.pointer;
			}
		}
		return true;	
	}

	
	void Service::set_name (string name) {
		s_description.name = name;
	}
	
	void Service::set_port (string port) {
		s_description.port = port;
	}
	
	void Service::set_address (string address) {
		s_description.address = address;
	}
	
	string Service::get_name () {
		return s_description.name;
	}
	
	string Service::get_port () {
		return s_description.port;
	}
	
	string Service::get_address () {
		return s_description.address;
	}
	
	Service_description* Service::get_description ()  {
		return new Service_description(s_description);
	}
	
	bool Service::send_service_request (int* socket) {
		if (!socket_initialization_client (socket, s_description.address, s_description.port)) return false;
		if (*socket == -1) {
			cerr << "\t\tERROR - Can't create the socket" << endl;
			return false;
		}
		
		send_string (*socket, s_description.name);	// ASYMMETRIC COMPARED TO RECEIVE
		send_int (*socket, parameters.size());
		if (!receive_int (*socket)) {
			cerr << "\t\tERROR - Wrong parameters number" << endl;
			return false;
		}
		
		for (int i = 0; i < (int) parameters.size(); i++) {
			if (!send_int (*socket, (int) parameters[i].type)) return false;
			if (!receive_int (*socket)) {
				cerr << "\t\tERROR - Wrong parameters type" << endl;
				return false;
			}
			
			if (parameters[i].type == Integer && !send_int (*socket, parameters[i].data.Integer)) return false;
			else if (parameters[i].type == Double && !send_double (*socket, parameters[i].data.Double)) return false;
			else if (parameters[i].type == String && !send_string (*socket, parameters[i].data.String)) return false;
			else if (parameters[i].type == Buffer && !send_buffer (*socket, &parameters[i].data.Buffer)) return false;
		}
		
		return true;
	}
	
	bool Service::receive_service_request (int socket) {
		if (receive_int (socket) == (int) parameters.size()) send_int (socket, (int) true);
		else {
			send_int (socket, (int) false);
			return false;
		}
		
		for (int i = 0; i < (int) parameters.size(); i++) {
			if(receive_int (socket) == (int) parameters[i].type ) send_int (socket, (int) true);
			else {
				send_int (socket, (int) false);
				return false;
			}
			
			if (parameters[i].type == Integer) parameters[i].data.Integer = receive_int (socket);
			else if (parameters[i].type == Double) parameters[i].data.Double = receive_double (socket);
			else if (parameters[i].type == String) parameters[i].data.String = receive_string (socket);
			else parameters[i].data.Buffer = *(receive_buffer (socket));		
		}
		
		return true;
	}
	
	bool Service::send_service_responce (int socket) {
		return responce.send_service_responce (socket);
	}
	
	bool Service::receive_service_responce (int socket) {
		bool result = responce.receive_service_responce (socket);
		
		close (socket);
		return result;		
	}

	
	bool Service::responce_decode (string folder_path) {
		Parameter responce_parameter;
		if (!responce.get_parameter (0, &responce_parameter)) return false;
		if (!make_image_from_buffer (folder_path, &responce_parameter.data.Buffer)) return false;
		
		free(parameters[0].data.Buffer.pointer);
		parameters[0].data.Buffer.size = 0;
		return true;
	}
	
	bool Service::responce_decode (vector<string> *file_list) {
		Parameter responce_parameter;
		if (!responce.get_parameter(0, &responce_parameter)) return false;
		
		char *result = NULL, *image_list = (char*) malloc (responce_parameter.data.String.length() + 1);
		strcpy(image_list, responce_parameter.data.String.c_str());
		image_list[responce_parameter.data.String.length()] = '\0';
		result = strtok(image_list, "\n");
		for (int i = 0; result != NULL; i++) {
			(*file_list).push_back(result);
			result = strtok (NULL, "\n");
		}
		return true;
	}