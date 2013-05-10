#ifndef Clients_functions_H_
#define Clients_functions_H_ 

	#include "../SOA_Library/Interface.h"
	#include "../SOA_Library/Threads.h"
	#include <time.h>

	#define IMAGES_DIRECTORY "Images/"
	#define CLIENT_DIRECTORY "./Work_directories/Clients/"
	#define REMOVE_DIRECTORY true
	
	int iteration_number;
	string SR_address, SR_port, client_number;

	bool check_client_arguments (int n_args, char** args){ // Checking arguments
		char* error = '\0';
		if (n_args < 2) {
			cout << "#CLIENT > Set iterations number of the client: ";
			cin >> iteration_number;
		}
		else iteration_number = atoi(args[1]);
		if (iteration_number < 1) return false;
		
		if (n_args < 3) {
			cout << "#CLIENT > Set Service_Register address: ";
			cin >> SR_address;
		}
		else SR_address = args[2];
		if (!check_address (SR_address)) return false;
		
		error = '\0';
		if (n_args < 4) {
			cout << "#CLIENT > Set Service_Register port [1024-65535]: ";
			cin >> SR_port;
		}
		else SR_port = args[3];
		if (error != '\0' ||  atoi(SR_port.c_str()) < 1023 ||  atoi(SR_port.c_str()) > 65535 ) return false;
		
		return true;
	}
	
	string choose_random_file (vector<string> folder_files) { // Choose random file from list
		if ((int) folder_files.size() == 0) return "";
		int random_choice = rand() % ((int) folder_files.size());
		
		return folder_files[random_choice];
	}

	void remove_working_directory () {
		if (!REMOVE_DIRECTORY) return;
		string command = "rm -rf " + string(CLIENT_DIRECTORY) + client_number + "/";
		if (system(command.c_str())) cerr << "#CLIENT > ERROR - Can't remove the working directory" << endl;
	}
	
#endif