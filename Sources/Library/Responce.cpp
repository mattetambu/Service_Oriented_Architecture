//Class Responce

#include "Responce.h"

	Responce::Responce (Service_description* s_description) {
		for (int i = 0; i < (int) s_description->p_description.size(); i++) 
			if (s_description->p_description[i].direction == OUT) add_parameter(s_description->p_description[i].type);
	}
	
	Responce::~Responce () {
		for (int i = 0; i < (int) parameters.size(); i++)
			if ((parameters[i].type == Buffer) && parameters[i].data.Buffer.size != 0) {
				free (parameters[i].data.Buffer.pointer);
				parameters[i].data.Buffer.size = 0;
			}
		parameters.clear();
	}
	
		
	void Responce::add_parameter(Type type) {
		parameters.resize(parameters.size()+1);
		parameters.back().type = type;
		//if(type == Buffer)
			parameters.back().data.Buffer.size = 0;
	}
	
	bool Responce::set_parameter(int index, Parameter *parameter) {
		if (parameter->type != parameters[index].type) return false;
		parameters[index] = *parameter;
		
		return true;
	}
	
	bool Responce::get_parameter (int index, Parameter* parameter) {
		if ((int) parameters.size() < index) return false;
		else *parameter = parameters[index];
		
		return true;
	}
	
	bool Responce::send_service_responce (int socket) {
		send_int (socket, parameters.size());
		if (!receive_int (socket)) {		
			cerr << SPACER << SPACER << "ERROR - Wrong parameters number in the responce request" << endl;
			return false;
		}
		
		for (int i = 0; i < (int) parameters.size(); i++) {
			if (!send_int (socket, (int) parameters[i].type)) return false;
			if (!receive_int (socket)) {
				cerr << SPACER << SPACER << "ERROR - Wrong parameters type in the responce request" << endl;
				return false;
			}
			
			if (parameters[i].type == Integer && !send_int (socket, parameters[i].data.Integer)) return false;
			else if (parameters[i].type == Double && !send_double (socket, parameters[i].data.Double)) return false;
			else if (parameters[i].type == String && !send_string (socket, parameters[i].data.String)) return false;
			else if (parameters[i].type == Buffer && !send_buffer (socket, &parameters[i].data.Buffer)) return false;
		}
		
		return true;
	}	
	
	bool Responce::receive_service_responce (int socket) {
		if (receive_int (socket) == (int) parameters.size()) send_int (socket, (int) true);
		else {
			send_int (socket, (int) false);
			cerr << SPACER << SPACER << "ERROR - Wrong parameters number for receiving the responce" << endl;
			return false;
		}
				
		for (int i = 0; i < (int) parameters.size(); i++) {
			if(receive_int (socket) == (int) parameters[i].type ) send_int (socket, (int) true);
			else {
				send_int (socket, (int) false);
				cerr << SPACER << SPACER << "ERROR - Wrong parameters type for receiving the responce" << endl;
				return false;
			}
			
			if (parameters[i].type == Integer) parameters[i].data.Integer = receive_int (socket);
			else if (parameters[i].type == Double) parameters[i].data.Double = receive_double (socket);
			else if (parameters[i].type == String) parameters[i].data.String = receive_string (socket);
			else parameters[i].data.Buffer = *(receive_buffer (socket));
		}
		return true;
	}
