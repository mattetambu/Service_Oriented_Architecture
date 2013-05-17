/**
 \file		Service_register_server_functions.h
 \dir		/Source/Application/Service_register_server/
 \date		15/05/2013
 \author	Tamburini Matteo <mattetambu@gmail.com>
 \brief		Raccolta di funzioni utili per l'implementazione del \e Service_register_server.
*/

/**
 \def		N_THREADS
 \brief		Numero di \e threads di servizio da avviare.
*/
 
/**
 \def		BACKLOG_QUEUE
 \brief		Dimensione della \e backlog \e queue associatta al \e listen_socket.
*/

/**
 \fn		bool check_server_arguments (int n_args, char** args)
 \param	[in]	n_args	Numero di argomenti in ingresso al \e Server.
 \param	[in]	args	Array di argomenti in ingresso al \e Server.
 \return	Risultato della verifica, \c true in caso di successo e \c false altrimenti.
 \brief		Controllo dei parametri della funzione main del \e Server.

 Al \e Server è necessario un solo parametro per la corretta esecuzione e se viene invocato privo di argomenti
 questa funzione ne richiede l'inserimento. Il parametro necessario al \e Server è un intero nell'intervallo [1024-65535]
 e rappresenta la porta di ascolto del \e Service_register_server.
*/

/**
 \fn		bool assign_execution_thread (int client_socket)
 \return	\c true in caso di assegnamento eseguito con successo, \c false altrimenti (tutti i \e threads sono occupati).
 \brief		Cerca fra i \e threads di servizio un \e thread libero e lo assegna all'esecuzione della richiesta
*/

/**
 \fn		bool Service_register_server_help ()
 \brief		Fornisce l'elenco dei comandi accettati dal \e Server.
*/

/**
 \fn		void* thread_body (void* thread_ID)
 \param	[in]	thread_ID	Intero che identifica il \e thread a cui è associata l'istanza della funzione.
 \brief		Corpo di tutti i \e threads di servizio del \e Service_register_server.

 Ogni \e thread di servizio, fino alla ricezione del comando di terminazione, esegue ciclicamente le seguenti operazioni:
 \li	segnala la sua disponibilità a ricevere connessioni e si pone in attesa di essere attivato per servire un \e Client
 \li	riceve il nome del servizio richiesto dal \e Client e se questo non corrisponde ad un servizio fornito rifiuta al richiesta
 \li	se la richiesta del \e Client viene accettata riceve i parametri necessari per l'esecuzione del servizio
 \li	richiama il servizio richiesto e, se necessario, invia al \e Client il risultato dell'esecuzione
*/

/**
 \fn		void* control_thread_body (void*)
 \brief		Corpo del \e thread di controllo del \e Service_register_server.

 Il \e thread di controllo, fino alla ricezione del comando di terminazione, esegue ciclicamente le seguenti operazioni:
 \li	si pone in attesa di essere attivato (manualmente) per eseguire un comando
 \li	richiede l'inserimento del comando e verifica se è in grado di eseguirlo (altrimenti lo rifiuta)
 \li	se il comando viene accettato esegue l'operazione corrispondente
*/


#ifndef Service_register_server_functions_H_
#define Service_register_server_functions_H_ 

	#include "../../SOA_Library/Interface.h"
	#include "../../SOA_Library/Threads.h"
	#include "./Service_register.h"
	
	#define N_THREADS 5
	#define BACKLOG_QUEUE 5
	
	Service_register* service_register = new Service_register();
	
	Threads thread[N_THREADS], control_thread;
	pthread_mutex_t mutex_thread_free;
	pthread_cond_t cond_thread_free;
	
	string SR_address, SR_port;
	int listen_socket;
	
	
	bool check_server_arguments (int n_args, char** args) { // Checking arguments
		if (n_args < 2) {
			cout << "#SERVER > Set Service_register_server port [1024-65535]: ";
			getline(cin, SR_port);
		}
		else SR_port = args[1];
		if (atoi(SR_port.c_str()) < 1023 ||  atoi(SR_port.c_str()) > 65535 ) return false;
		
		SR_address = get_my_ip();
		cout << "#SERVER > Service_register_server running on  " << SR_address << ":" << SR_port << endl;
		return true;
	}

	bool assign_execution_thread (int client_socket) {
		int i = 0;
		while (i < N_THREADS)
			if (thread[i].test_and_set_busy()) {
				thread[i].set_socket(client_socket);
				thread[i].thread_start();
				break;
			}
			else i++;
		
		return (i != N_THREADS);
	}
	
	bool Service_register_server_help () {
		cout << SPACER << "Command format:" << endl;
		cout << SPACER << SPACER << "command" << endl;
		cout << SPACER << "Accepted command list:" << endl;
		cout << SPACER << SPACER << "print_register" << endl;
		cout << SPACER << SPACER << "help" << endl;
		cout << SPACER << SPACER << "quit" << endl;
		
		return true;
	}

	void* thread_body (void* thread_ID) {
		int ID = ((int) thread_ID);
		bool service_result;
		string request, name, address, port;
		Service_description* s_description;
		
		while (thread[ID].is_active()) {
			pthread_cond_signal(&cond_thread_free);
			thread[ID].wait_start();
			if (!thread[ID].is_active()) break;
			
			service_result = false;
			cout << endl << "#SERVER > Client connetted" << endl;
			request = receive_string (thread[ID].get_socket());
			cout << "#SERVER > Service request: " << request << endl;
			
			if (request == "add_service_provider") {
				if (send_int (thread[ID].get_socket(), (int) REQUEST_ACCEPTED) && 
					(address = receive_string (thread[ID].get_socket())) != "" && 
					(port = receive_string (thread[ID].get_socket())) != "") {
						if (!(service_result = service_register->add_service_provider (address, port)))
							cout << "#SERVER > Server already registered" << endl;
						else cout << "#SERVER > Request for service add_service_provider served" << endl;
				}
			}
			else if (request == "remove_service_provider") {
				if (send_int (thread[ID].get_socket(), (int) REQUEST_ACCEPTED) && 
					(address = receive_string (thread[ID].get_socket())) != "" && 
					(port = receive_string (thread[ID].get_socket())) != "") {
						
						if (!(service_result = service_register->remove_service_provider (address, port)))
							cout << "#SERVER > Service provider not registered" << endl;
						else cout << "#SERVER > Request for service remove_service_provider served" << endl;
				}
			}
			else if (request == "add_service") {
				if (send_int (thread[ID].get_socket(), (int) REQUEST_ACCEPTED) && 
				   (s_description = receive_service_description (thread[ID].get_socket())) != NULL &&
					s_description->name != "") {
						if (!(service_result = service_register->add_service(s_description)))
							cout << "#SERVER > Service " << name << " already registered" << endl;
						else cout << "#SERVER > Request for adding service " << name << " served" << endl;
				}
			}
			else if (request == "remove_service") {
				if (send_int (thread[ID].get_socket(), (int) REQUEST_ACCEPTED) && 
					(name = receive_string (thread[ID].get_socket())) != "" && 
					(address = receive_string (thread[ID].get_socket())) != "" && 
					(port = receive_string (thread[ID].get_socket())) != "") {
						if (!(service_result = service_register->remove_service(name, address, port)))
							cout << "#SERVER > Service " << name << " not registered" << endl;
						else cout << "#SERVER > Request for removing service " << name << " served" << endl;
				}
			}
			else if (request == "get_service") {
				if (send_int (thread[ID].get_socket(), (int) REQUEST_ACCEPTED) && 
					(name = receive_string (thread[ID].get_socket())) != "") {
						s_description = service_register->get_service(name);
						if (s_description == NULL) cout << "#SERVER > Service " << name << " not registered" << endl;
						if ((service_result = send_service_description (thread[ID].get_socket(), s_description)))
							cout << "#SERVER > Request for getting service " << name << " served" << endl;
				}
			}
			else send_int (thread[ID].get_socket(), (int) REQUEST_NOT_ACCEPTED);
			
			if (!service_result) cout << "#SERVER > Can't serve the " << request << " request" << endl;
			close(thread[ID].get_socket());
			thread[ID].set_free();
		}
		return 0;
	}

	void* control_thread_body (void*) {
		while (control_thread.is_active()) {
			bool result = false;
			string activate, command = "", operand = "";
			getline(cin, activate);
			
			cout << "#SERVER > (Insert a command) ";
			getline(cin, command);
			operand = (command.find(' ') == string::npos)? "" : command.substr(command.find(' ')+1);
			command = command.substr(0, command.find_first_of(' '));

			if (command == "help" && operand == "") result = Service_register_server_help ();
			else if (command == "print_register" && operand == "") result = service_register->print_register();
			else if (command == "quit" && operand == "") {
				control_thread.thread_exit();
				shutdown(listen_socket, SHUT_RDWR);
				result = true;
			}
			else {
				cout << "#SERVER >  Can't execute the command - Command unknown" << endl;
				continue;
			}
			
			if (result) cout << "#SERVER > Command executed" << endl;
			else cout << "#SERVER > Command not executed" << endl;
		}
		return 0;
	}


#endif