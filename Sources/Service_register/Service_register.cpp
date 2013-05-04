//Class Service_register

#include "Service_register.h"
#include "../Image_manipulation/Rotate_image.h"
#include "../Image_manipulation/Horizontal_flip_image.h"
#include "../Image_storage/Store_image.h"
#include "../Image_storage/Get_image.h"
#include "../Image_storage/Get_list.h"

#include "../Image_manipulation/Rotate_image.cpp"
#include "../Image_manipulation/Horizontal_flip_image.cpp"
#include "../Image_storage/Store_image.cpp"
#include "../Image_storage/Get_image.cpp"
#include "../Image_storage/Get_list.cpp"


	Service_register::Service_register() {}
	Service_register::~Service_register() {}

	void Service_register::add_service_provider (string address, string port) {}
	void Service_register::remove_service_provider (string address, string port) {}

	void Service_register::add_service (Service_description* s_description) {}
	void Service_register::remove_service (string name, string address, string port) {}
	
	Service_description* Service_register::get_service (string requested_service_name) {
		Service* requested_service;
		if (requested_service_name == "horizontal_flip_image") requested_service = new Horizontal_flip_image ("horizontal_flip_image", "127.0.0.1", "23457");
		else if (requested_service_name == "rotate_image") requested_service = new Rotate_image ("rotate_image", "127.0.0.1", "23457");
		else if (requested_service_name == "store_image") requested_service = new Store_image ("store_image", "127.0.0.1", "34568");
		else if (requested_service_name == "get_image") requested_service = new Get_image ("get_image", "127.0.0.1", "34568");
		else requested_service = new Get_list ("get_list", "127.0.0.1", "34568");
		
		return requested_service->get_description();	
	}
	void Service_register::print_register() {}
