//USAGE: Image_manipulation_server ${Image_manipulation_server_port} ${Service_register_server_address} ${Service_register_server_port}

#include "./Application/Image_manipulation_server/Image_manipulation_server_functions.h"


int main (int n_args, char ** args) {
	cout << "******* Image manipulation server *******" << endl << endl;
	
	if (!check_server_arguments (n_args, args)) {
		cerr << "#SERVER > ERROR - Invalid argument" << endl;
		exit(-1);
	}
	if (!socket_initialization_server (&listen_socket, SP_port, (int) BACKLOG_QUEUE)) {
		cerr << "#SERVER > ERROR - Can't create a listen socket correctly" << endl;
		exit(-1);
	}
	
	
	// Registering services
	horizontal_flip_image = new Horizontal_flip_image ("horizontal_flip_image", SP_address, SP_port);
	rotate_image = new Rotate_image ("rotate_image", SP_address, SP_port);
		
	cout << "#SERVER > Registering image_manipulation server" << endl;
	if (!register_service_provider (SP_address, SP_port)) cerr << "#SERVER > " << SPACER << " ERROR - Can't register the server" << endl;
	else {
		cout << "#SERVER > Registering horizontal_flip_image service" << endl;
		if (!register_service (horizontal_flip_image)) cerr << "#SERVER > " << SPACER << " ERROR - Can't register the horizontal_flip_image service" << endl;
	
		cout << "#SERVER > Registering rotate_image service" << endl;
		if (!register_service (rotate_image)) cerr << "#SERVER > " << SPACER << " ERROR - Can't register the rotate_image service" << endl;
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
	if (pthread_create(&thread_ID, NULL, control_thread_body, NULL) != 0)  {
		cerr << "#SERVER > ERROR - Can't create the control thread" << endl;
		exit(-1);			
	}
	control_thread.set_ID (thread_ID);
	
	
	cout << "\n#SERVER > Waiting for connections" << endl;
	while (control_thread.is_active()) {
		int client_socket = accept_client_connection (listen_socket);
		if (client_socket == -1)  {
			if (control_thread.is_active()) cerr << "#SERVER > ERROR - Can't accept the connection with the client" << endl;
			continue;
		}
		
		while (!assign_execution_thread (client_socket)) pthread_cond_wait (&cond_thread_free, &mutex_thread_free);
	}


	// Closing sockets and threads
	for (int i = 0; i < N_THREADS; i++) {
		thread[i].thread_exit();
		pthread_join(thread[i].get_ID(), NULL);
	}
	pthread_join(control_thread.get_ID(), NULL);
	
	shutdown(listen_socket, SHUT_RDWR);
	close(listen_socket);
	
	
	// Unregistering services - Only unregister_service_provider is needed
	cout << "#SERVER > Unregistering horizontal_flip_image service" << endl;
	if (!unregister_service (horizontal_flip_image->get_description())) cerr << "#SERVER > " << SPACER << " ERROR - Can't unregister the horizontal_flip_image service" << endl;
	delete (horizontal_flip_image);
	
	cout << "#SERVER > Unregistering rotate_image service" << endl;
	if (!unregister_service (rotate_image->get_description())) cerr << "#SERVER > " << SPACER << " ERROR - Can't unregister the rotate_image service" << endl;
	delete (rotate_image);
	
	cout << "#SERVER > Unregistering image_manipulation server" << endl;
	if (!unregister_service_provider (SP_address, SP_port)) cerr << "#SERVER > " << SPACER << " ERROR - Can't unregister the server" << endl;
	
	
	cout << endl << "#SERVER > Server closed" << endl;
	cout << endl << "***********************" << endl;
	exit(0);
}
