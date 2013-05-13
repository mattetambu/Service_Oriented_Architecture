//Class Store_image

#ifndef Store_image_H_
#define Store_image_H_

	#include "../../SOA_Library/Service.h"

	#define IMAGES_STORAGE_DIRECTORY "./Work_directories/Servers/Image_storage_server/"	
		

	class Store_image : public Service {
		private:
			string path;
			void inizialize_parameters (string path);
		
		public:
			Store_image ();
			Store_image (string name, string address, string port);
			Store_image (string name, string address, string port, string path);
			Store_image (Service_description* s_description);
			Store_image (Service_description* s_description, string path);
			virtual ~Store_image ();
			
			bool execute ();
	};

#endif
