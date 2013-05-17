/**
 \file		Image_manipulation_server_functions.h
 \dir		/Source/Application/Image_manipulation_server/
 \date		15/05/2013
 \author	Tamburini Matteo <mattetambu@gmail.com>
 \brief		Raccolta di funzioni utili per l'implementazione dell' \e Image_manipulation_server.
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

 Al \e Server sono necessari tre parametri per la sua esecuzione e se viene invocato con un numero inferiore di argomenti 
 questa funzione richiede l'inserimento di quelli mancanti. Il controllo sui parametri necessari al \e Server viene effettuato nel seguente modo:
 \li	il primo deve essere un intero nell'intervallo [1024-65535] e rappresenta la porta di ascolto dell' \e Image_manipulation_server
 \li	il secondo deve essere un indirizzo IP e rappresenta l'indirizzo IP del \e Service_register_server
 \li	il terzo deve essere un intero nell'intervallo [1024-65535] e rappresenta la porta di ascolto del \e Service_register_server
*/

/**
 \fn		bool assign_execution_thread (int client_socket)
 \return	\c true in caso di assegnamento eseguito con successo, \c false altrimenti (tutti i \e threads sono occupati).
 \brief		Cerca fra i \e threads di servizio un \e thread libero e lo assegna all'esecuzione della richiesta
*/

/**
 \fn		bool Image_manipulation_server_help ()
 \brief		Fornisce l'elenco dei comandi accettati dal \e Server.
*/

/**
 \fn		void* thread_body (void* thread_ID)
 \param	[out]	thread_ID	Intero che identifica il \e thread a cui è associata l'istanza della funzione.
 \brief		Corpo di tutti i \e threads di servizio dell' \e Image_manipulation_server.

 Ogni \e thread di servizio, fino alla ricezione del comando di terminazione, esegue ciclicamente le seguenti operazioni:
 \li	segnala la sua disponibilità a ricevere connessioni e si pone in attesa di essere attivato per servire un \e Client
 \li	riceve il nome del servizio richiesto dal \e Client e se questo non corrisponde ad un servizio fornito rifiuta al richiesta
 \li	se la richiesta del \e Client viene accettata riceve i parametri necessari per l'esecuzione del servizio
 \li	richiama il servizio richiesto (rotazione o riflessione dell'immagine) ottenendo il risultato della manipolazione
 \li	invia al \e Client il risultato dell'esecuzione del servizio
*/

/**
 \fn		void* control_thread_body (void*)
 \brief		Corpo del \e thread di controllo dell' \e Image_manipulation_server.

 Il \e thread di controllo, fino alla ricezione del comando di terminazione, esegue ciclicamente le seguenti operazioni:
 \li	si pone in attesa di essere attivato (manualmente) per eseguire un comando
 \li	richiede l'inserimento del comando e verifica se è in grado di eseguirlo (altrimenti lo rifiuta)
 \li	se il comando viene accettato esegue l'operazione corrispondente
*/


#ifndef Image_manipulation_server_functions_H_
#define Image_manipulation_server_functions_H_ 

	#include "../../SOA_Library/Interface.h"
	#include "../../SOA_Library/Threads.h"
	#include "./Horizontal_flip_image.h"
	#include "./Rotate_image.h"
	
	#define N_THREADS 5
	#define BACKLOG_QUEUE 5

	Rotate_image* rotate_image;
	Horizontal_flip_image* horizontal_flip_image;
	
	Threads thread[N_THREADS], control_thread;
	pthread_mutex_t mutex_thread_free;
	pthread_cond_t cond_thread_free;
	
	string SP_address, SR_address, SP_port, SR_port;
	int listen_socket;


	bool check_server_arguments (int n_args, char** args) { // Checking arguments
		if (n_args < 2) {
			cout << "#SERVER > Set Image_manipulation_server port [1024-65535]: ";
			getline(cin, SP_port);
		}
		else SP_port = args[1];
		if (atoi(SP_port.c_str()) < 1023 ||  atoi(SP_port.c_str()) > 65535 ) return false;
		
		if (n_args < 3) {
			cout << "#SERVER > Set Service_register_server address: ";
			getline(cin, SR_address);
		}
		else SR_address = args[2];
		if (!check_address (SR_address)) return false;
		
		if (n_args < 4) {
			cout << "#SERVER > Set Service_register_server port [1024-65535]: ";
			getline(cin, SR_port);
		}
		else SR_port = args[3];
		if (atoi(SR_port.c_str()) < 1023 ||  atoi(SR_port.c_str()) > 65535 ) return false;
		
		SP_address = get_my_ip();
		cout << "#SERVER > Image_manipulation_server running on  " << SP_address << ":" << SP_port << endl;
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
	
	bool Image_manipulation_server_help () {
		cout << SPACER << "Command format:" << endl;
		cout << SPACER << SPACER << "command [operand]" << endl;
		cout << SPACER << "Accepted command list:" << endl;
		cout << SPACER << SPACER << "register_server" << endl;
		cout << SPACER << SPACER << "unregister_server" << endl;
		cout << SPACER << SPACER << "register_service operand" << endl;
		cout << SPACER << SPACER << "unregister_service operand" << endl;
		cout << SPACER << SPACER << "help" << endl;
		cout << SPACER << SPACER << "quit" << endl;
		cout << SPACER << "Accepted operand list:" << endl;
		cout << SPACER << SPACER << "rotate_image" << endl;
		cout << SPACER << SPACER << "horizontal_flip_image" << endl;
		
		return true;
	}

	void *thread_body (void* thread_ID) {
		int ID = (int) thread_ID;
			
		while (thread[ID].is_active()) {
			pthread_cond_signal(&cond_thread_free);
			thread[ID].wait_start();
			if (!thread[ID].is_active()) break;
			
			cout << endl << "#SERVER > Client connetted" << endl;
			string service = receive_string(thread[ID].get_socket());
			cout << "#SERVER > Service request: " << service << endl;
			
			if (service == "rotate_image") {
				rotate_image->receive_service_request(thread[ID].get_socket());
				rotate_image->execute();
				rotate_image->send_service_responce(thread[ID].get_socket());
				
				cout << "#SERVER > Request for service rotate_image served" << endl;
			}
			else if (service == "horizontal_flip_image") {
				horizontal_flip_image->receive_service_request(thread[ID].get_socket());
				horizontal_flip_image->execute();
				horizontal_flip_image->send_service_responce(thread[ID].get_socket());
				
				cout << "#SERVER > Request for service horizontal_flip_image served" << endl;
			}
			else {
				send_int (thread[ID].get_socket(), (int) REQUEST_NOT_ACCEPTED);	// REQUEST NOT ACCEPTED
				cout << "#SERVER > Can't serve the request - Service " << service << " unknown" << endl;
			}
			
			close(thread[ID].get_socket());
			thread[ID].set_free();
		}
		return 0;
	}

	void *control_thread_body (void*) {
		while (control_thread.is_active()) {
			bool result = false;
			string activate, command = "", operand = "";
			getline(cin, activate);
			
			cout << "#SERVER > (Insert a command) ";
			getline(cin, command);
			operand = (command.find(' ') == string::npos)? "" : command.substr(command.find(' ')+1);
			command = command.substr(0, command.find_first_of(' '));
			
			if (command == "register_server" && operand == "") result = register_service_provider (SP_address, SP_port);
			else if (command == "unregister_server" && operand == "") result = unregister_service_provider (SP_address, SP_port);
			else if (command == "register_service") {
				if (operand == "rotate_image") result = register_service (rotate_image->get_description());
				else if (operand == "horizontal_flip_image") result = register_service (horizontal_flip_image->get_description());
				else cout << "#SERVER > Can't register the service - Service " << operand.c_str() << " unknown" << endl;
			}
			else if (command == "unregister_service") {
				if (operand == "rotate_image") result = unregister_service (rotate_image->get_description());
				else if (operand == "horizontal_flip_image") result = unregister_service (horizontal_flip_image->get_description());
				else cout << "#SERVER > Can't unregister the service - Service " << operand.c_str() << " unknown" << endl;
			}
			else if (command == "help" && operand == "") result = Image_manipulation_server_help ();
			else if (command == "quit" && operand == "") {
				control_thread.thread_exit();
				shutdown(listen_socket, SHUT_RDWR);
				result = true;
			}
			else {
				cout << "#SERVER > Can't execute the command - Command unknown" << endl;
				continue;
			}
			
			if (result) cout << "#SERVER > Command executed" << endl;
			else cout << "#SERVER > Command not executed" << endl;
		}
		return 0;
	}

#endif