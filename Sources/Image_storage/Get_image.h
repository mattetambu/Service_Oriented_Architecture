//Class Get_image

#ifndef Get_image_H_
#define Get_image_H_

#include "../Library/Service.h"
#include "../Library/Files_manager.h"

#define IMAGES_STORAGE_DIRECTORY "./Files/Servers/Image_storage_server/"	
	

class Get_image: public Service {
	string path;
	
	public:
	
	Get_image ();
	Get_image (string name, string address, string port);
	Get_image (string name, string address, string port, string path);
	Get_image (Service_description* s_description);
	Get_image (Service_description* s_description, string path);
	virtual ~Get_image ();
	
	void inizialize_parameters (string path);
	bool execute ();
};

#endif
