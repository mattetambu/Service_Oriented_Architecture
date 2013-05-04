//Class Horizontal_flip_image

#ifndef Horizontal_flip_image_H_
#define Horizontal_flip_image_H_

#include "../Library/Service.h"
//#include <Magick++.h>

//using namespace Magick;

#define FLIP_IMAGE_DIRECTORY "./Files/Servers/Image_manipulation_server/Horizontal_flip_image/"	


class Horizontal_flip_image : public Service {
	string path;
	
	public:

	Horizontal_flip_image ();
	Horizontal_flip_image (string name, string address, string port);
	Horizontal_flip_image (string name, string address, string port, string path);
	Horizontal_flip_image (Service_description* s_description);
	Horizontal_flip_image (Service_description* s_description, string path);
	virtual ~Horizontal_flip_image ();
		
	void inizialize_parameters (string path);
	bool execute ();
};

#endif
