/**
 \file		Socket_io.h
 \dir		/Source/SOA_Library/
 \date		15/05/2013
 \author	Tamburini Matteo <mattetambu@gmail.com>
 \brief		Funzioni per lo scambio di dati su un \e Socket.
*/

/**
 \fn		bool socket_initialization_client (int* client_socket, string address, string port)
 \param	[out]	client_socket	\e Socket da utilizzare per effettuare la connessione con il \e Server
 \param	[in]	address	Indirizzo IP del \e Server al quale si intende connettersi
 \param	[in]	port	Porta di ascolto del \e Server al quale si intende connettersi
 \return	Risultato della connessione, \c true in caso di successo e \c false altrimenti.
 \brief		Crea un \e Socket di tipo SOCK_STREAM e lo utilizza per connettersi al \e Server il cui endpoint è passato come parametro
*/

/**
 \fn		bool socket_initialization_server (int* listen_socket, string port, int backlog_queue_length)
 \param	[out]	listen_socket	\e Socket di ascolto da utilizzare per accettare la connessione dei \e Clients
 \param	[in]	port	Porta di ascolto del \e Server
 \param	[in]	backlog_queue_length	Dimensione della coda di backlog da usare come parametro per la primitiva \c listen
 \return	Risultato della creazione del \e Socket di ascolto, \c true in caso di successo e \c false altrimenti.
 \brief		Crea un \e Socket di tipo SOCK_STREAM e lo utilizza per le primitive \c bind e \c listen
*/

/**
 \fn		int accept_client_connection (int listen_socket)
 \param	[in]	listen_socket	\e Socket di ascolto del \e Server.
 \return	Risultato della primitiva \c accept effettuata sul \e Socket passato come parametro.
 \brief		Esegue la primitiva \c accept sul \e Socket passato come parametro.
*/

/**
 \fn		bool check_address (string address)
 \param	[in]	address	Stringa da testare per verificare se rispetta il formato di un indirizzo IP.
 \return	Risultato del test, \c true se la stringa rappresenta un indirizzo IP valido e \c false altrimenti.
 \brief		Testa se la stringa passata come parametro rappresenta un indirizzo IP valido.
*/

/**
 \fn		string get_my_ip ()
 \return	Stringa che rappresenta l'indirizzo IP del chiamante.
 \brief		Restituisce l'indirizzo IP del chiamante.
*/

/**
 \fn		bool send_int (int socket, int data)
 \param	[in]	socket	\e Socket per l'invio del dato.
 \param	[in]	data	Dato di tipo intero da inviare sul \e Socket.
 \return	Risultato dell'invio del dato, \c true in caso di successo e \c false altrimenti.
 \brief		Invia l'intero passato come parametro sul \e Socket specificato.
*/

/**
 \fn		bool send_double (int socket, double data)
 \param	[in]	socket	\e Socket per l'invio del dato.
 \param	[in]	data	Dato di tipo double da inviare sul \e Socket.
 \return	Risultato dell'invio del dato, \c true in caso di successo e \c false altrimenti.
 \brief		Invia il double passato come parametro sul \e Socket specificato.
*/

/**
 \fn		bool send_string (int socket, string data)
 \param	[in]	socket	\e Socket per l'invio del dato.
 \param	[in]	data	Dato di tipo stringa da inviare sul \e Socket.
 \return	Risultato dell'invio del dato, \c true in caso di successo e \c false altrimenti.
 \brief		Invia la stringa passata come parametro sul \e Socket specificato.
*/

/**
 \fn		bool send_buffer (int socket, buffer* data)
 \param	[in]	socket	\e Socket per l'invio del dato.
 \param	[in]	data	Dato di tipo buffer da inviare sul \e Socket.
 \return	Risultato dell'invio del dato, \c true in caso di successo e \c false altrimenti.
 \brief		Invia il buffer passato come parametro sul \e Socket specificato.
*/

/**
 \fn		bool send_service_description (int socket, Service_description* s_description)
 \param	[in]	socket	\e Socket per l'invio della descrizione di un servizio.
 \param	[in]	s_description	Descrizione del servizio da inviare sul \e Socket.
 \return	Risultato dell'invio della descrizione, \c true in caso di successo e \c false altrimenti.
 \brief		Invia la descrizione del servizio passata come parametro sul \e Socket specificato.
 
 L'invio della descrizione del servizio passata come parametro avviene nel seguente modo:
 \li	invio del nome del servizio
 \li	invio dell'indirizzo del service provider che offre il servizio descritto
 \li	invio della porta di ascolto del service provider che offre il servizio descritto
 \li	invio del numero di parametri necessari al servizio (sia di ingresso che di uscita)
 \li	per ogni parametro invia la direzione [IN/OUT]	e il tipo
*/

/**
 \fn		int receive_int (int socket)
 \param	[in]	socket	\e Socket per la ricezione del dato.
 \return	Risultato della ricezione, dato di tipo intero in caso di successo e \c -1 altrimenti.
 \brief		Riceve un intero sul \e Socket specificato.
*/

/**
 \fn		double receive_double (int socket)
 \param	[in]	socket	\e Socket per la ricezione del dato.
 \return	Risultato della ricezione, dato di tipo double in caso di successo e \c -1 altrimenti.
 \brief		Riceve un double sul \e Socket specificato.
*/

/**
 \fn		string receive_string (int socket)
 \param	[in]	socket	\e Socket per la ricezione del dato.
 \return	Risultato della ricezione, dato di tipo stringa in caso di successo e una stringa vuota altrimenti.
 \brief		Riceve una stringa sul \e Socket specificato.
*/

/**
 \fn		buffer* receive_buffer (int socket)
 \param	[in]	socket	\e Socket per la ricezione del dato.
 \return	Risultato della ricezione, dato di tipo buffer in caso di successo e \c NULL altrimenti.
 \brief		Riceve un buffer sul \e Socket specificato.
*/

/**
 \fn		Service_description* receive_service_description (int socket)
 \param	[in]	socket	\e Socket per la ricezione della descrizione di un servizio.
 \return	Descrizione del servizio ricevuta true in caso di successo e \c NULL altrimenti.
 \brief		Riceve la descrizione del servizio sul \e Socket specificato e la ritorna al chiamante.
 
 La ricezione della descrizione del servizio avviene nel seguente modo:
 \li	ricezione del nome del servizio
 \li	ricezione dell'indirizzo del service provider che offre il servizio descritto
 \li	ricezione della porta di ascolto del service provider che offre il servizio descritto
 \li	ricezione del numero di parametri necessari al servizio (sia di ingresso che di uscita)
 \li	Per ogni parametro riceve la direzione [IN/OUT]	e il tipo
*/


#ifndef Socket_io_H_
#define Socket_io_H_

	#include "Types.h"

	#include <netdb.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>


	bool socket_initialization_client (int* client_socket, string address, string port);
	bool socket_initialization_server (int* listen_socket, string port, int backlog_queue_length);
	int accept_client_connection (int listen_socket);
	bool check_address (string address);
	string get_my_ip ();
	
	bool send_int (int socket, int data);
	bool send_double (int socket, double data);
	bool send_string (int socket, string data);
	bool send_buffer (int socket, buffer* data);
	bool send_service_description (int socket, Service_description* s_description);

	int receive_int (int socket);
	double receive_double (int socket);
	string receive_string (int socket);
	buffer* receive_buffer (int socket);
	Service_description* receive_service_description (int socket);
	
#endif
