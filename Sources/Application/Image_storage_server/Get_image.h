//Class Get_image

#ifndef Get_image_H_
#define Get_image_H_

	#include "../../SOA_Library/Service.h"

	#define IMAGES_STORAGE_DIRECTORY "./Work_directories/Servers/Image_storage_server/"	
		

	class Get_image: public Service {
		private:
			string path;
			void inizialize_parameters (string path);
		
		public:
			Get_image ();
			Get_image (string name, string address, string port);
			Get_image (string name, string address, string port, string path);
			Get_image (Service_description* s_description);
			Get_image (Service_description* s_description, string path);
			virtual ~Get_image ();
			
			bool execute ();
	};

#endif
