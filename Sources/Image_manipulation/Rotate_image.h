//Class Rotate_image

#ifndef Rotate_image_H_
#define Rotate_image_H_

#include "../Library/Service.h" 
//#include <Magick++.h>

//using namespace Magick;

#define ROTATE_IMAGE_DIRECTORY "./Files/Servers/Image_manipulation_server/Rotate_image/"	


class Rotate_image : public Service {
	string path;
	
	public:

	Rotate_image ();
	Rotate_image (string name, string address, string port);
	Rotate_image (string name, string address, string port, string path);
	Rotate_image (Service_description* s_description);
	Rotate_image (Service_description* s_description, string path);
	virtual ~Rotate_image ();
	
	void inizialize_parameters (string path);
	bool execute ();
};

#endif
