//Class Responce

#ifndef Responce_H_
#define Responce_H_

	#include "./Socket_io.h"


	class Responce {
		private:
			vector<Parameter> parameters;

		public:
			Responce () {}
			Responce (Service_description* s_description);
			virtual ~Responce ();
			
			void add_parameter(Type type);
			bool set_parameter(int index, Parameter* parameter);
			bool get_parameter (int index, Parameter* parameter);
			
			bool send_service_responce (int socket);
			bool receive_service_responce (int socket);
	};

#endif
