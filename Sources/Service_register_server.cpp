//USAGE: Service_register_server ${Service_register_server_port}

#include "./Application/Service_register_server/Service_register_server_functions.h"


int main (int n_args, char ** args) {
	cout << "******* Service register server *******" << endl << endl;
	
	if (!check_server_arguments (n_args, args)) {
		cout << "#SERVER > ERROR - Invalid argument" << endl;
		exit(-1);
	}
	if (!socket_initialization_server (&listen_socket, SR_port, (int) BACKLOG_QUEUE)) {
		cout << "#SERVER > ERROR - Can't create a listen socket correctly" << endl;
		exit(-1);
	}
	
	
	// Creating threads
	pthread_t thread_ID;
	
	for (int i = 0; i < N_THREADS; i++) {
		if (pthread_create(&thread_ID, NULL, thread_body, (void *) i) != 0) {
			cout << "#SERVER > ERROR - Can't create a service thread" << endl;
			exit(-1);			
		}
		thread[i].set_ID (thread_ID);
	}
	if (pthread_create(&thread_ID, NULL, control_thread_body, NULL) != 0)  {
		cout << "#SERVER > ERROR - Can't create the control thread" << endl;
		exit(-1);			
	}
	control_thread.set_ID (thread_ID);
	
	
	cout << "#SERVER > Waiting for connections" << endl;
	while (control_thread.is_active()) {
		int client_socket = accept_client_connection (listen_socket);
		if (client_socket == -1)  {
			if (control_thread.is_active()) cout << "#SERVER > ERROR - Can't accept the connection with the client" << endl;
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
	
	delete service_register;
	
	
	cout << endl << "#SERVER > Server closed" << endl;
	cout << endl << "***********************" << endl;
	exit(0);
}
