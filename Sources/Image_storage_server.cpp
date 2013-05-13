//USAGE: Image_storage_server ${Image_storage_server_port} ${Service_register_server_address} ${Service_register_server_port}

#include "./Application/Image_storage_server/Image_storage_server_functions.h"


int main (int n_args, char ** args) {
	cout << "******* Image storage server *******" << endl << endl;
	
	if (!check_server_arguments (n_args, args)) {
		cerr << "#SERVER > ERROR - Invalid argument" << endl;
		exit(-1);
	}
	if (!socket_initialization_server (&listen_socket, SP_port, (int) BACKLOG_QUEUE)) {
		cerr << "#SERVER > ERROR - Can't create a listen socket correctly" << endl;
		exit(-1);
	}
	
	
	// Registering services
	store_image = new Store_image ("store_image", SP_address, SP_port);
	get_image = new Get_image ("get_image", SP_address, SP_port);
	get_list = new Get_list ("get_list", SP_address, SP_port);
	
	cout << "#SERVER > Registering image_storage server" << endl;
	if (!register_service_provider (SP_address, SP_port)) cerr << "#SERVER > " << SPACER << "ERROR - Can't register the server" << endl;
	else {
		cout << "#SERVER > Registering store_image service" << endl;
		if (!register_service (store_image)) cerr << "#SERVER > " << SPACER << "ERROR - Can't register the store_image service" << endl;
		
		cout << "#SERVER > Registering get_image service" << endl;
		if (!register_service (get_image)) cerr << "#SERVER > " << SPACER << "ERROR - Can't register the get_image service" << endl;
	
		cout << "#SERVER > Registering get_list service" << endl;
		if (!register_service (get_list)) cerr << "#SERVER > " << SPACER << "ERROR - Can't register the get_list service" << endl;
	}
	
	// Initializing mutex
	pthread_mutex_init (&mutex_1, NULL);
	pthread_mutex_init (&mutex_2, NULL);
	pthread_mutex_init (&mutex_thread_free, NULL);
	pthread_cond_init (&cond_thread_free, NULL);
	readers_count = 0;
	
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
	cout << "#SERVER > Unregistering store_image service" << endl;
	if (!unregister_service (store_image->get_description())) cerr << "#SERVER > " << SPACER << "ERROR - Can't unregister the store_image service" << endl;
	delete (store_image);
	
	cout << "#SERVER > Unregistering get_image service" << endl;
	if (!unregister_service (get_image->get_description())) cerr << "#SERVER > " << SPACER << "ERROR - Can't unregister the get_image service" << endl;
	delete (get_image);
	
	cout << "#SERVER > Unregistering get_list service" << endl;
	if (!unregister_service (get_list->get_description())) cerr << "#SERVER > " << SPACER << "ERROR - Can't unregister the get_list service" << endl;
	delete (get_list);
	
	cout << "#SERVER > Unregistering image_storage server" << endl;
	if (!unregister_service_provider (SP_address, SP_port)) cerr << "#SERVER > " << SPACER << "ERROR - Can't unregister the server" << endl;
	
	
	cout << endl << "#SERVER > Server closed" << endl;
	cout << endl << "***********************" << endl;
	exit(0);
}
