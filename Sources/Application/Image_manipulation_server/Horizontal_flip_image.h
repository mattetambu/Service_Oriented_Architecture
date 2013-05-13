//Class Horizontal_flip_image

#ifndef Horizontal_flip_image_H_
#define Horizontal_flip_image_H_

	#include "../../SOA_Library/Service.h"
	#include <Magick++.h>
	#include <sstream>

	using namespace Magick;

	#define FLIP_IMAGE_DIRECTORY "./Work_directories/Servers/Image_manipulation_server/Horizontal_flip_image/"
	#define REMOVE_IMAGES true


	class Horizontal_flip_image : public Service {
		private:	
			string path;
			void inizialize_parameters (string path);
		
		public:

			Horizontal_flip_image ();
			Horizontal_flip_image (string name, string address, string port);
			Horizontal_flip_image (string name, string address, string port, string path);
			Horizontal_flip_image (Service_description* s_description);
			Horizontal_flip_image (Service_description* s_description, string path);
			virtual ~Horizontal_flip_image ();
			
			bool execute ();
	};

#endif
