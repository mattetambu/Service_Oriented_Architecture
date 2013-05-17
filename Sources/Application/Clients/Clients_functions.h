/**
 \file		Client_functions.cpp
 \dir		/Source/Application/Clients/
 \date		15/05/2013
 \author	Tamburini Matteo <mattetambu@gmail.com>
 \brief		Raccolta di funzioni utili per l'implementazione del \e Client.
*/

/**
 \def		IMAGES_DIRECTORY
 \brief		Percorso della directory contenente le immagini.
*/
 
/**
 \def		CLIENT_DIRECTORY
 \brief		Percorso della directory di lavoro dei clients.
*/

/**
 \def		REMOVE_DIRECTORY
 \brief		Definisce se rimuovere o meno la directory di lavoro privata del \e Client una volta completata la sua esecuzione.
*/

/**
 \fn		bool check_client_arguments (int n_args, char** args)
 \param	[in]	n_args	Numero di argomenti in ingresso al \e Client.
 \param	[in]	args	Array di argomenti in ingresso al \e Client.
 \return	Risultato della verifica, \c true in caso di successo e \c false altrimenti.
 \brief		Controllo dei parametri della funzione main del \e Client.

 Al \e Client sono necessari tre parametri per la sua esecuzione e se viene invocato con un numero inferiore di argomenti 
 questa funzione richiede l'inserimento di quelli mancanti. Il controllo sui parametri necessari al \e Client viene effettuato nel seguente modo:
 \li	il primo deve essere un intero >= 1 e rappresenta il numero di iterazioni che il \e Client deve effettuare
 \li	il secondo deve essere un indirizzo IP e rappresenta l'indirizzo IP del \e Service_register_server
 \li	il terzo deve essere un intero nell'intervallo [1024-65535] e rappresenta la porta di ascolto del \e Service_register_server
*/

/**
 \fn		string choose_random_element (vector<string> elements)
 \param	[in]	elements	Vettore di stringhe
 \return	Stringa scelta.
 \brief		Sceglie in modo random un elemento del vettore passato come parametro e lo ritorna al chiamante.
*/

/**
 \fn		void remove_working_directory ()
 \brief		Rimuove la directory di lavoro privata del \e Client se \c REMOVE_DIRECTORY è settata a \c true
*/


#ifndef Clients_functions_H_
#define Clients_functions_H_ 

	#include "../../SOA_Library/Interface.h"
	#include "../../SOA_Library/Threads.h"
	#include <time.h>

	#define IMAGES_DIRECTORY "./Images/"
	#define CLIENT_DIRECTORY "./Work_directories/Clients/"
	#define REMOVE_DIRECTORY true
	
	int iteration_number;
	string SR_address, SR_port, client_number = "";

	bool check_client_arguments (int n_args, char** args) { // Checking arguments
		char* error = '\0';
		if (n_args < 4) cout << endl << endl;
		if (n_args < 2) {
			cout << "#CLIENT > Set iterations number of the client: ";
			cin >> iteration_number;
		}
		else iteration_number = atoi(args[1]);
		if (iteration_number < 1) return false;
		
		if (n_args < 3) {
			cout << "#CLIENT > Set Service_register_server address: ";
			cin >> SR_address;
		}
		else SR_address = args[2];
		if (!check_address (SR_address)) return false;
		
		error = '\0';
		if (n_args < 4) {
			cout << "#CLIENT > Set Service_register_server port [1024-65535]: ";
			cin >> SR_port;
		}
		else SR_port = args[3];
		if (error != '\0' ||  atoi(SR_port.c_str()) < 1023 ||  atoi(SR_port.c_str()) > 65535 ) return false;
		
		return true;
	}
	
	string choose_random_element (vector<string> elements) { // Choose random element from list
		srand(time(NULL));
		if ((int) elements.size() == 0) return "";
		
		return elements[rand() % ((int) elements.size())];
	}

	void remove_working_directory () {
		if (!REMOVE_DIRECTORY || client_number == "") return;
		
		string command = "rm -rf " + string(CLIENT_DIRECTORY) + client_number + "/";
		if (system(command.c_str())) cerr << "#CLIENT > ERROR - Can't remove the working directory" << endl;
	}
	
#endif