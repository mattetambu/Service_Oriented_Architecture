//Class Get_list

#ifndef Get_list_H_
#define Get_list_H_

#include "../SOA_Library/Service.h"

#define IMAGES_STORAGE_DIRECTORY "./Work_directories/Servers/Image_storage_server/"	
	

class Get_list : public Service{
	private:
		string path;
		void inizialize_parameters (string path);
	
	public:
		Get_list ();
		Get_list (string name, string address, string port);
		Get_list (string name, string address, string port, string path);
		Get_list (Service_description* s_description);
		Get_list (Service_description* s_description, string path);
		virtual ~Get_list ();
			
		bool execute ();
};

#endif
