/**
 \file		Interface.h
 \dir		/Source/SOA_Library/
 \date		15/05/2013
 \author	Tamburini Matteo <mattetambu@gmail.com>
 \brief		Funzioni necessarie a \e Clients e \e Servers per interfacciarsi con il \e Service_register_server.
*/

/**
 \fn		bool register_service_provider (string address, string port)
 \param	[in]	address	Indirizzo IP del \e Service_register_server.
 \param	[in]	port	Porta di ascolto del \e Service_register_server.
 \return	Risultato della registrazione del service provider, \c true in caso di successo e \c false altrimenti.
 \brief		Registrazione del service provider nel registro del \e Service_register_server.

 Le azioni intraprese dal service provider per la registrazione al \e Service_register_server risultano:
 \li	instaurare una connessione con il \e Service_register_server
 \li	inviare la richiesta di registrazione e attendere la conferma dell'avvenuta accettazione della richiesta
 \li	inviare l'indirizzo IP e la porta di ascolto del service provider stesso
 \li	chiudere la connessione con il \e Service_register_server
*/

/**
 \fn		bool unregister_service_provider (string address, string port)
 \param	[in]	address	Indirizzo IP del \e Service_register_server.
 \param	[in]	port	Porta di ascolto del \e Service_register_server.
 \return	Risultato della cancellazione del service provider, \c true in caso di successo e \c false altrimenti.
 \brief		Cancellazione del service provider dal registro del \e Service_register_server.

 Le azioni intraprese dal service provider per la cancellazione dal registro del \e Service_register_server
 (che comporta la cancellazione dal registro dei servizi di tutti i servizi offerti dal service provider) risultano:
 \li	instaurare una connessione con il \e Service_register_server
 \li	inviare la richiesta di cancellazione e attendere la conferma dell'avvenuta accettazione della richiesta
 \li	inviare l'indirizzo IP e la porta di ascolto del service provider stesso
 \li	chiudere la connessione con il \e Service_register_server
*/

/**
 \fn		bool register_service (Service_description* s_description)
 \param	[in]	s_description	Descrizione del servizio da registrare al \e Service_register_server.
 \return	Risultato della registrazione del servizio, \c true in caso di successo e \c false altrimenti.
 \brief		Registrazione del servizio offerto dal service provider nel registro del \e Service_register_server.

 Le azioni intraprese per la registrazione del servizio offerto dal service provider al \e Service_register_server risultano:
 \li	instaurare una connessione con il \e Service_register_server
 \li	inviare la richiesta di registrazione e attendere la conferma dell'avvenuta accettazione della richiesta
 \li	inviare la descrizione del servizio offerto da inserire nel registro del \e Service_register_server
 \li	chiudere la connessione con il \e Service_register_server
*/

/**
 \fn		bool unregister_service (Service_description* s_description)
 \param	[in]	s_description	Descrizione del servizio da cancellare dal \e Service_register_server.
 \return	Risultato della cancellazione del servizio, \c true in caso di successo e \c false altrimenti.
 \brief		Cancellazione del servizio dal registro del \e Service_register_server.

 Le azioni intraprese per la cancellazione del servizio dal registro del \e Service_register_server risultano:
 \li	instaurare una connessione con il \e Service_register_server
 \li	inviare la richiesta di cancellazione e attendere la conferma dell'avvenuta accettazione della richiesta
 \li	inviare la descrizione del servizio da cancellare dal registro del \e Service_register_server
 \li	chiudere la connessione con il \e Service_register_server
*/
	
/**
 \fn		Service* service_request (string service)
 \param	[in]	service	Nome del servizio da richiedere al \e Service_register_server.
 \return	Servizio inizializzato con la descrizione fornita dal registro del \e Service_register_server ( \c NULL se il servizio non è presente nel registro).
 \brief		Richiesta effettuata per ottenere le informazioni relative a un servizio registrato al \e Service_register_server.

 Le azioni intraprese dal \e Client per richiedere le informazioni relative a un servizio registrato al \e Service_register_server risultano:
 \li	instaurare una connessione con il \e Service_register_server
 \li	inviare la richiesta di informazioni relative al servizio e attendere la conferma dell'avvenuta accettazione della richiesta
 \li	inviare il nome del servizio ricercato e ricevere la descrizione del servizio stesso 
 \li	chiudere la connessione con il \e Service_register_server
*/


#ifndef Interface_H_
#define Interface_H_

	#include "./Service.h"
	#include <dirent.h>


	extern string SR_address, SR_port;

	bool register_service_provider (string address, string port);
	bool unregister_service_provider (string address, string port);
	
	bool register_service (Service_description* s_description);
	bool unregister_service (Service_description* s_description);
	
	Service* service_request (string service);

#endif