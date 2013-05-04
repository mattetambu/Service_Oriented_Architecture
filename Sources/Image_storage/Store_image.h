//Class Store_image

#ifndef Store_image_H_
#define Store_image_H_

#include "../Library/Service.h"
#include "../Library/Interface.h"
#include "../Library/Files_manager.h"

#define IMAGES_STORAGE_DIRECTORY "./Files/Servers/Image_storage_server/"	
	

class Store_image : public Service {
	string path;
	
	public:
	
	Store_image ();
	Store_image (string name, string address, string port);
	Store_image (string name, string address, string port, string path);
	Store_image (Service_description* s_description);
	Store_image (Service_description* s_description, string path);
	virtual ~Store_image ();
	
	void inizialize_parameters (string path);
	
	bool execute ();
};

#endif
