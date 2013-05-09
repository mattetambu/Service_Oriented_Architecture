//Classe Service

#ifndef Service_H_
#define Service_H_

#include "Types.h"
#include "Socket_io.h"
#include "Files_manager.h"
#include "Responce.h"

#define REQUEST_ACCEPTED 1
#define REQUEST_NOT_ACCEPTED 0

class Service {
	protected:
	
		Service_description s_description;
		vector<Parameter> parameters;
		Responce responce;
		
	public:

		Service () {}
		Service (string name, string address, string port);
		Service (Service_description* s_description);
		virtual ~Service ();
		
		void add_parameter (Direction direction, Type type);
		bool set_input_parameters (vector<Parameter> parameters);			
		
		void set_name (string name);
		void set_port (string port);
		void set_address (string address);
		string get_name ();
		string get_port ();
		string get_address ();
		Service_description* get_description ();
		
		bool send_service_request (int* socket);
		bool receive_service_request (int socket);
		bool send_service_responce (int socket);
		bool receive_service_responce (int socket);
		
		bool virtual responce_decode (string folder_path);
		bool virtual responce_decode (vector<string> *file_list);
		bool virtual execute () { return true; }
};
	
#endif
