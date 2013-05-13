//Class Rotate_image

#ifndef Rotate_image_H_
#define Rotate_image_H_

	#include "../../SOA_Library/Service.h"
	#include <Magick++.h>
	#include <sstream>

	using namespace Magick;

	#define ROTATE_IMAGE_DIRECTORY "./Work_directories/Servers/Image_manipulation_server/Rotate_image/"
	#define REMOVE_IMAGES true


	class Rotate_image : public Service {
		private:
			string path;
			void inizialize_parameters (string path);
		
		public:
			Rotate_image ();
			Rotate_image (string name, string address, string port);
			Rotate_image (string name, string address, string port, string path);
			Rotate_image (Service_description* s_description);
			Rotate_image (Service_description* s_description, string path);
			virtual ~Rotate_image ();
			
			bool execute ();
	};

#endif
