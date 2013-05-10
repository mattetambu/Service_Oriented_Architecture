//USAGE: Client ${Client_iteretions} ${Service_register_server_address} ${Service_register_server_port}

#include "./Clients/Clients_functions.h"


int main (int n_args, char ** args) {
	atexit (remove_working_directory);
	cout << "******* Client *******";
	
	if (!check_client_arguments (n_args, args)) {
		cerr << endl << endl << "#CLIENT > ERROR - Invalid argument" << endl;
		exit(-1);
	}
	
	if ((client_number = make_working_directory(CLIENT_DIRECTORY)) == "") {
		cerr << "#CLIENT > ERROR - Can't create the working directory" << endl;
		exit(-1);
	}
	
	srand(time(NULL));
	for (int i = 0; i < iteration_number; i++) {
		cout << endl << endl;
		sleep(1);
		//cin.get();
		
		cout << "******* Iteration numeber " << i << " *******" << endl;
		
		string required_service_name = (rand() % 2)? "rotate_image" : "horizontal_flip_image";
		string file_choice = (rand() % 2)? "from_disk" : "from_server";
		string disk_image_name, server_image_name, result_image_path = CLIENT_DIRECTORY + client_number + "/";
		string image_path, image_name = (required_service_name == "rotate_image")? "rotated_" : "flipped_";
		int service_socket, degrees = rand() % 360;
		vector<Parameter> parameters;

		if (file_choice == "from_server"){	//******************************** GETTING IMAGE FROM STORAGE SERVER ***************************************
			cout << "#CLIENT > Choosing an image from service provider" << endl;
			
			//************************************ LOOKING FOR GET_LIST SERVICE *********************************************
			cout << "#CLIENT > " << SPACER << " Looking for a get_list service" << endl;
			Service* get_list_service = service_request("get_list");
			if(get_list_service == NULL) {
				cout << "#CLIENT > " << SPACER << SPACER << " ERROR - Service get_list now unaviable" << endl;
				continue;
			}
			
			
			//************************************ REQUIRING GET_LIST SERVICE *********************************************
			cout << "#CLIENT > " << SPACER << " Sending request for service get_list to service provider" << endl;
			if(!get_list_service->send_service_request(&service_socket)) {
				cerr << "#CLIENT > " << SPACER << SPACER << " ERROR - Can't send the service request" << endl;
				exit(-1);	
			}
			if(!get_list_service->receive_service_responce(service_socket)) {
				cerr << "#CLIENT > " << SPACER << SPACER << " ERROR - Can't receive the responce from the service" << endl;
				exit(-1);	
			}
			
			vector<string> server_image_list;
			get_list_service->responce_decode (&server_image_list);
			if ((int) server_image_list.size() == 0) {
				cerr << "#CLIENT > " << SPACER << SPACER << " ERROR - No image stored in the server" << endl;
				continue;
			}
			else server_image_name = choose_random_file(server_image_list);		
			//delete get_list_service;
			
			cout << "#CLIENT > " << SPACER << " Service get_list successfully completed" << endl;
			cout << "#CLIENT > " << SPACER << " Choosed image: " << server_image_name << endl;
			
			
			
			//************************************ LOOKING FOR GET_IMAGE SERVICE *********************************************
			cout << "#CLIENT > " << SPACER << " Looking for a get_image service" << endl;
			Service* get_image_service = service_request("get_image");
			if(get_image_service == NULL) {
				cout << "#CLIENT > " << SPACER << SPACER << " ERROR - Service get_image now unaviable" << endl;
				continue;
			}

			
			//************************************** COMPILING GET_IMAGE SERVICE PARAMETERS ***********************************************
			//cerr <<"#CLIENT > " << SPACER << " Setting parameters for requiring get_image service" << endl;
			parameters.clear();		
			parameters.resize(1);
			parameters[0].type = String;
			parameters[0].data.String = server_image_name;
		
			if (!get_image_service->set_input_parameters(parameters)) {
				cerr <<"#CLIENT > " << SPACER << SPACER << " ERROR - Parameters do not correspond to those required by the provider" << endl;
				exit(-1);
			}
	
	
			//************************************** REQUIRING GET_IMAGE SERVICE ***********************************************
			cout << "#CLIENT > " << SPACER << " Sending request for service get_image to service provider" << endl;
			if(!get_image_service->send_service_request(&service_socket)) {
				cerr << "#CLIENT > " << SPACER << SPACER << " ERROR - Can't send the service request" << endl;
				exit(-1);	
			}
			if(!get_image_service->receive_service_responce(service_socket)) {
				cerr << "#CLIENT > " << SPACER << SPACER << " ERROR - Can't receive the responce from the service" << endl;
				exit(-1);	
			}
						
			image_path = CLIENT_DIRECTORY + client_number + "/" + server_image_name;
			get_image_service->responce_decode (image_path);
			image_name += server_image_name;

			cout << "#CLIENT > " << SPACER << " Service get_image successfully completed" << endl;
			
			//delete get_image_service;
		}
		else {	//************************************** GETTING IMAGE FROM DISK ***********************************************
			cout << "#CLIENT > Choosing an image from disk" << endl;
			
			vector<string> disk_image_list;
			if (!make_file_list (string(IMAGES_DIRECTORY), &disk_image_list)) continue;
			if ((int) disk_image_list.size() == 0) {
				cerr << "#CLIENT > " << SPACER << SPACER << " ERROR - No image stored in the disk" << endl;
				continue;
			}
			else disk_image_name = choose_random_file (disk_image_list);

			cout << "#CLIENT > " << SPACER << " Choosed image: " << disk_image_name << endl;
			image_path = IMAGES_DIRECTORY + disk_image_name;
			image_name += disk_image_name;
		}
		result_image_path += image_name;
		
		
		
		//************************************ LOOKING FOR CHOOSED SERVICE *********************************************
		cout <<"#CLIENT > Requiring service " << required_service_name;
		if (required_service_name == "rotate_image") cout <<" (" << degrees << "°) " << endl;
		else cout << endl;
		cout << "#CLIENT > " << SPACER << " Looking for a " << required_service_name << " service" << endl;
		Service* required_service = service_request (required_service_name);			
		if(required_service == NULL) {
			cout << "#CLIENT > " << SPACER << " ERROR - Service " << required_service_name << " now unaviable" << endl;
			continue;
		}
		
		
		//************************************** COMPILING CHOOSED SERVICE PARAMETERS ***********************************************
		//cerr <<"#CLIENT > " << SPACER << " Setting parameters for requiring choosed service" << endl;
		int index = 0;
		parameters.clear();
		if (required_service_name == "rotate_image") { 
			parameters.resize(2);
			parameters[index].type = Integer;
			parameters[index].data.Integer = degrees;
			index++;
		}
		else if (required_service_name == "horizontal_flip_image") parameters.resize(1);
		parameters[index].type = Buffer;
		
		if (!get_buffer_from_image (image_path, &parameters[index].data.Buffer)) continue;
		
		if (!required_service->set_input_parameters(parameters)) {
			cerr <<"#CLIENT > " << SPACER << SPACER << " ERROR - Parameters do not correspond to those required by the provider" << endl;
			exit(-1);
		}

		
		//************************************** REQUIRING CHOOSED SERVICE ***********************************************
		cout << "#CLIENT > " << SPACER << " Sending request for service " << required_service_name << " to service provider" << endl;
		
		if(!required_service->send_service_request(&service_socket)) {
			cerr << "#CLIENT > " << SPACER << SPACER << " ERROR - Can't send the service request" << endl;
			exit(-1);	
		}
		if(!required_service->receive_service_responce(service_socket)) {
			cerr << "#CLIENT > " << SPACER << SPACER << " ERROR - Can't receive the responce from the service" << endl;
			exit(-1);	
		}
				
		required_service->responce_decode (result_image_path);
		//delete required_service;
		
		cout << "#CLIENT > " << SPACER << " Service " << required_service_name << " successfully completed" << endl;
		
		
		
		//************************************** LOOKING FOR IMAGE STORAGE SERVER ***********************************************
		cout << "#CLIENT > Requiring service store_image" << endl;
		cout << "#CLIENT > " << SPACER << " Looking for a store_image service" << endl;
		Service* store_image_service = service_request("store_image");		
		if(store_image_service == NULL) {
			cout << "#CLIENT > " << SPACER << SPACER << " ERROR - Service store_image now unaviable" << endl;
			continue;
		}
		
		
		//************************************** COMPILING STORE_IMAGE SERVICE PARAMETERS ***********************************************
		//cerr <<"#CLIENT > " << SPACER << " Setting parameters for requiring store_image service" << endl;
		parameters.clear();
		parameters.resize(2);
		parameters[0].type = String;
		parameters[0].data.String = image_name; 
		parameters[1].type = Buffer;
		
		if (!get_buffer_from_image (result_image_path, &parameters[1].data.Buffer)) continue;
			
		if (!store_image_service->set_input_parameters(parameters)) {
			cerr <<"#CLIENT > " << SPACER << SPACER << " ERROR - Parameters do not correspond to those required by the provider" << endl;
			exit(-1);
		}
		
		//************************************** SENDING IMAGE TO SERVER ***********************************************
		cout << "#CLIENT > " << SPACER << " Sending request for service store_image to service provider" << endl;
		if(!store_image_service->send_service_request(&service_socket)) {
			cerr << "#CLIENT > " << SPACER << SPACER << " ERROR - Can't send the service request" << endl;
			exit(-1);	
		}
		if(!store_image_service->receive_service_responce(service_socket)) {
			cerr << "#CLIENT > " << SPACER << SPACER << " ERROR - Can't receive the responce from the service" << endl;
			exit(-1);	
		}
		cout << "#CLIENT > " << SPACER << " Service store_image successfully completed" << endl;

		
		//************************************** REQUEST COMPLETED ***********************************************
		//delete store_image_service;
		parameters.clear();
	}
	cout << endl << "**********************" << endl;
	exit(0);
}
