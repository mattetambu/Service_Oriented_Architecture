//USAGE: Service_register_server ${Service_register_server_port}

#include "./Service_register/Service_register_server_functions.h"


Service_register* service_register = new Service_register();
Threads thread[N_THREADS], control_thread;
string SR_address, SR_port;

int main (int n_args, char ** args) {
	cout << "******* Service register server *******" << endl << endl;
	int listen_socket;
	
	if (!check_server_arguments (n_args, args)) {
		cout << "#SERVER > ERROR - Invalid argument" << endl;
		exit(-1);
	}
	if (!socket_initialization_server (&listen_socket, SR_port, (int)N_THREADS)) {
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
	/*if (pthread_create(&thread_ID, NULL, control_thread_body, NULL) != 0)  {
		cout << "#SERVER > ERROR - Can't create the control thread" << endl;
		exit(-1);			
	}
	control_thread.set_ID (thread_ID);*/
	
	
	cout << "#SERVER > Waiting for connections" << endl;
	//while (control_thread.is_active()) {
	while (true) {
		int client_address_lenght, client_socket;
		sockaddr_in client_address;
		cout << endl;
			
		client_address_lenght = sizeof(client_address);
		memset (&client_address, 0, client_address_lenght);
		client_socket = accept(listen_socket, (sockaddr *) &client_address, (socklen_t*) &client_address_lenght);
		if (client_socket == -1)  {
			cout << "#SERVER > ERROR - Can't accept the connection with the client" << endl;
			continue;
		}
		
		//if (!control_thread.is_active()) break;
		for (int i = 0; i < N_THREADS; i++) {
			if (thread[i].test_and_set_busy()) {
				thread[i].set_socket(client_socket);
				thread[i].thread_start();
				break;
			}
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
	
	
	cout << "#SERVER > Server closed" << endl;
	exit(0);
}
