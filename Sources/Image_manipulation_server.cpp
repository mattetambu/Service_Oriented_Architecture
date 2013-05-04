//USAGE: Image_manipulation_server ${Image_manipulation_server_port} ${Service_register_server_address} ${Service_register_server_port}

#include "./Image_manipulation/Image_manipulation_server_functions.h"


Rotate_image* rotate_image;
Horizontal_flip_image* horizontal_flip_image;
Threads thread[N_THREADS], control_thread;
string SP_address, SR_address, SP_port, SR_port;


int main (int n_args, char ** args) {
	cout << " ******* Image manipulation server *******" << endl << endl;
	int listen_socket;
	
	if (!check_server_arguments (n_args, args)) {
		cerr << "#SERVER > ERROR - Invalid argument" << endl;
		exit(-1);
	}
	if (!socket_initialization_server (&listen_socket, SP_port, (int)N_THREADS)) {
		cerr << "#SERVER > ERROR - Can't create a listen socket correctly" << endl;
		exit(-1);
	}
	
	
	// Registering services
	horizontal_flip_image = new Horizontal_flip_image ("horizontal_flip_image", SP_address, SP_port);
	rotate_image = new Rotate_image ("rotate_image", SP_address, SP_port);
		
	cout << "#SERVER > Registering image_manipulation server" << endl;
	if (!register_service_provider (SP_address, SP_port)) cerr << "#SERVER > ERROR - Unable to register the server" << endl;
	else {
		cout << "#SERVER > Registering horizontal_flip_image service" << endl;
		if (!register_service (horizontal_flip_image)) cerr << "#SERVER > ERROR - Unable to register the horizontal_hlip_image service" << endl;
	
		cout << "#SERVER > Registering rotate_image service" << endl;
		if (!register_service (rotate_image)) cerr << "#SERVER > ERROR - Unable to register the rotate_image service" << endl;
	}
	
	// Creating threads
	pthread_t thread_ID;
	
	for (int i = 0; i < N_THREADS; i++) {
		if (pthread_create(&thread_ID, NULL, thread_body, (void*) i) != 0) {
			cerr << "#SERVER > ERROR - Can't create a service thread" << endl;
			exit(-1);			
		}
		thread[i].set_ID (thread_ID);
	}
	/*if (pthread_create(&thread_ID, NULL, control_thread_body, NULL) != 0)  {
		cerr << "#SERVER > ERROR - Can't create the control thread" << endl;
		exit(-1);			
	}
	control_thread.set_ID (thread_ID);*/
	
	
	cout << "\n#SERVER > Waiting for connections" << endl;
	//while (control_thread.is_active()) {
	while (true) {
		int client_address_lenght, client_socket;
		sockaddr_in client_address;
			
		client_address_lenght = sizeof(client_address);
		memset (&client_address, 0, client_address_lenght);
		client_socket = accept (listen_socket, (sockaddr *) &client_address, (socklen_t*) &client_address_lenght);
		if (client_socket == -1)  {
			cerr << "#SERVER > ERROR - Can't accept the connection with the client" << endl;
			continue;
		}
		
		//if (!control_thread.is_active()) break;
		for (int i = 0; i < N_THREADS; i++)
			if (thread[i].test_and_set_busy()) {
				thread[i].set_socket(client_socket);
				thread[i].thread_start();
				break;
			}
	}


	// Closing sockets and threads
	for (int i = 0; i < N_THREADS; i++) {
		thread[i].thread_exit();
		pthread_join(thread[i].get_ID(), NULL);
	}
	pthread_join(control_thread.get_ID(), NULL);
	
	shutdown(listen_socket, SHUT_RDWR);
	close(listen_socket);
	
	
	// Unregistering services
	cout << "#SERVER > Unregistering horizontal_flip_image service" << endl;
	if (!unregister_service (horizontal_flip_image->get_description())) cerr << "#SERVER > ERROR - Unable to unregister the horizontal_hlip_image service" << endl;
				
	cout << "#SERVER > Unregistering rotate_image service" << endl;
	if (!unregister_service (rotate_image->get_description())) cerr << "#SERVER > ERROR - Unable to unregister the rotate_image service" << endl;
	
	cout << "#SERVER > Unregistering image_manipulation server" << endl;
	if (!unregister_service_provider (SP_address, SP_port)) cerr << "#SERVER > ERROR - Unable to unregister the server" << endl;
	
	
	cout << "#SERVER > Server closed" << endl;
	exit(0);
}
