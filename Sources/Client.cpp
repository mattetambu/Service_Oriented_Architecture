#include "./Clients/Clients_functions.h"

int iteration_number;
string SR_address, SR_port;

using namespace std;

int main (int n_args, char ** args) {
	cout << " ******* Client *******";
	
	if (!check_client_arguments (n_args, args)) {
		cerr << endl << endl << "#CLIENT > ERROR - Invalid argument" << endl;
		exit(-1);
	}
	
	srand(time(NULL));
	for (int i = 0; i < iteration_number; i++) {
		string required_service_name = (rand() % 2)? "rotate_image" : "horizontal_flip_image";
		string file_choice = (rand() % 2)? "from_disk" : "from_server";
		string disk_image_name, server_image_name, image_path_after_service = CLIENT_DIRECTORY; // TO BE RENAMED
		string image_path, image_name = (required_service_name == "rotate_image")? "rotated_" : "flipped_";
		
		vector<Parameter> parameters;
		int service_socket;

		cout << endl << endl;
		sleep(1);
		//cin.get();
		
		if (file_choice == "from_server"){	//******************************** LOOKING FOR IMAGE STORAGE SERVER ***************************************
			cout << "#CLIENT > Choosing an image from service provider" << endl;
			cout << "#CLIENT > " << SPACER << " Looking for a get_list service" << endl;
			Service* get_list_service = service_request("get_list");
			if(get_list_service == NULL) {
				cout << "#CLIENT > " << SPACER << SPACER << " ERROR - Service get_list now unaviable" << endl;
				continue;
			}
			
			cout << "#CLIENT > " << SPACER << " Sending get_list request to service provider" << endl;
			if(!get_list_service->send_service_request(&service_socket)) {
				cerr << "#CLIENT > " << SPACER << SPACER << " ERROR - Unable to send the service request" << endl;
				continue;	
			}
			if(!get_list_service->receive_service_responce(service_socket)) {
				cerr << "#CLIENT > " << SPACER << SPACER << " ERROR - Unable to receive the responce from the service" << endl;
				continue;	
			}
					
			vector<string> server_image_list;
			get_list_service->responce_decode (&server_image_list);
			if ((int) server_image_list.size() == 0) {
				cerr << "#CLIENT > " << SPACER << SPACER << " ERROR - No image stored in the server" << endl;
				continue;
			}
			else server_image_name = choose_random_file(server_image_list);		
			delete get_list_service;
			
						
			
			//************************************** GETTING IMAGE FROM SERVER ***********************************************
			cout << "#CLIENT > " << SPACER << " Looking for a get_image service" << endl;
			Service* get_image_service = service_request("get_image");
			if(get_image_service == NULL) {
				cout << "#CLIENT > " << SPACER << SPACER << " ERROR - Service get_image now unaviable" << endl;
				continue;
			}

			parameters.resize(1);
			parameters[0].type = String;
			parameters[0].data.String = server_image_name;
		
			if (!get_image_service->set_input_parameters(parameters)) {
				cerr <<"#CLIENT > " << SPACER << SPACER << " ERROR - Parameters do not correspond to those required by the provider" << endl;
				continue;
			}
	
			cout << "#CLIENT > " << SPACER << " Sending get_image request to service provider" << endl;
			if(!get_image_service->send_service_request(&service_socket)) {
				cerr << "#CLIENT > " << SPACER << SPACER << " ERROR - Unable to send the service request" << endl;
				continue;	
			}
			if(!get_image_service->receive_service_responce(service_socket)) {
				cerr << "#CLIENT > " << SPACER << SPACER << " ERROR - Unable to receive the responce from the service" << endl;
				continue;	
			}
						
			cout << "#CLIENT > " << SPACER << " Choosed image: " << server_image_name << endl;
			image_path = CLIENT_DIRECTORY + server_image_name;
			get_image_service->responce_decode (image_path);
			image_name += server_image_name;

			parameters.clear();		
			delete get_image_service;
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
		image_path_after_service += image_name;	// TO BE RENAMED
		
		
		//************************************ LOOKING FOR CHOOSED SERVICE *********************************************
		cout <<"#CLIENT > Requiring service " << required_service_name << endl;
		cout << "#CLIENT > " << SPACER << " Looking for a " << required_service_name << " service" << endl;
		Service* required_service = service_request (required_service_name);			
		if(required_service == NULL) {
			cout << "#CLIENT > " << SPACER << " ERROR - Service " << required_service_name << " now unaviable" << endl;
			continue;
		}
		
		
		//************************************** COMPILING CHOOSED SERVICE PARAMETERS ***********************************************
		cerr <<"#CLIENT > " << SPACER << " Setting parameters for requiring choosed service" << endl;
		int index = 0;
		if (required_service_name == "rotate_image") { 
			parameters.resize(2);
			parameters[index].type = Integer;
			parameters[index].data.Integer = rand() % 360;
			index++;
		}
		else if (required_service_name == "horizontal_flip_image") parameters.resize(1);
		parameters[index].type = Buffer;
		
		if (!get_buffer_from_image (image_path, &parameters[index].data.Buffer)) {
			parameters[index].data.Buffer.size = 0;
			parameters[index].data.Buffer.pointer = NULL;
			continue;
		}
		
		if (!required_service->set_input_parameters(parameters)) {
			cerr <<"#CLIENT > " << SPACER << SPACER << " ERROR - Parameters do not correspond to those required by the provider" << endl;
			continue;
		}
		parameters.clear();

		
		//************************************** REQUIRING CHOOSED SERVICE ***********************************************
		cout << "#CLIENT > " << SPACER << " Sending request for service " << required_service_name << " to service provider" << endl;
		if(!required_service->send_service_request(&service_socket)) {
			cerr << "#CLIENT > " << SPACER << SPACER << " ERROR - Unable to send the service request" << endl;
				continue;	
		}
		if(!required_service->receive_service_responce(service_socket)) {
			cerr << "#CLIENT > " << SPACER << SPACER << " ERROR - Unable to receive the responce from the service" << endl;
			continue;	
		}
				
		required_service->responce_decode (image_path_after_service);
		delete required_service;
		
		
		//************************************** LOOKING FOR IMAGE STORAGE SERVER ***********************************************
		cout << "#CLIENT > Requiring service store_image" << endl;
		cout << "#CLIENT > " << SPACER << " Looking for a store_image service" << endl;
		required_service = service_request("store_image");		
		if(required_service == NULL) {
			cout << "#CLIENT > " << SPACER << SPACER << " ERROR - Service store_image now unaviable" << endl;
			continue;
		}
		
		//************************************** SENDING IMAGE TO SERVER ***********************************************
		parameters.clear();
		parameters.resize(2);

		parameters[0].type = String;
		parameters[0].data.String = image_name; 
		parameters[1].type = Buffer;
		
		if (!get_buffer_from_image (image_path_after_service, &parameters[1].data.Buffer)) {
			parameters[1].data.Buffer.size = 0;
			parameters[1].data.Buffer.pointer = NULL;
			continue;
		}
			
		if (!required_service->set_input_parameters(parameters)) {
			cerr <<"#CLIENT > " << SPACER << SPACER << " ERROR - Parameters do not correspond to those required by the provider" << endl;
			continue;
		}

		cout << "#CLIENT > " << SPACER << " Sending request for service store_image to service provider" << endl;
		if(!required_service->send_service_request(&service_socket)) {
			cerr << "#CLIENT > " << SPACER << SPACER << " ERROR - Unable to send the service request" << endl;
			continue;	
		}
		if(!required_service->receive_service_responce(service_socket)) {
			cerr << "#CLIENT > " << SPACER << SPACER << " ERROR - Unable to receive the responce from the service" << endl;
			continue;	
		}
		

		//************************************** REQUEST COMPLETED ***********************************************
		delete required_service;
	}
}
