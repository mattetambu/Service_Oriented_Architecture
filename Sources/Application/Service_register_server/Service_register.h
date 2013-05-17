/**
 \file		Service_register.h
 \dir		/Source/Application/Service_register_server/
 \date		15/05/2013
 \author	Tamburini Matteo <mattetambu@gmail.com>
 \brief		Classe che implementa il registro dei servizi.
*/

/** 
 \class		Service_register
 \brief		Classe che implementa il registro dei servizi. Qui vengono registrati i servizi forniti dai vari service provider.
*/

/**
 \fn		Service_register::Service_register ()
 \brief		Costruttore di default della classe Service_register. Inizializza i semafori di mutua esclusione.
*/

/**
 \fn		virtual Service_register::~Service_register ()
 \brief		Distruttore della classe Service_register.
*/

/**
 \fn		void readers_prologue ()
 \brief		Se i files sono occupati da uno scrittore attende il turno dei lettori, altrimenti occupa i files permettendone l'accesso ai soli i lettori.
*/

/**
 \fn		void readers_epilogue ()
 \brief		Segnala la fine dell'elaborazione del \e thread lettore e se questo è l'ultimo lettore attivo rilascia la mutua esclusione.
*/

/**
 \fn		void writers_prologue ()
 \brief		Attende il proprio turno per l'accesso ai files che deve avvenire in mutua esclusione.
*/

/**
 \fn		void writers_epilogue()
 \brief		Segnala la fine dell'elaborazione del \e thread scrittore e rilascia la mutua esclusione.
*/

/**
 \fn		bool Service_register::add_service_provider (string address, string port)
 \param	[in]	address	Indirizzo IP del service provider.
 \param	[in]	port	Porta di ascolto del service provider.
 \return	Risultato dell'esecuzione, \c true in caso di successo e \c false altrimenti.
 \brief		Aggiunge al registro il service provider il cui endpoint è passato come parametro.
*/

/**
 \fn		bool Service_register::remove_service_provider (string address, string port)
 \param	[in]	address	Indirizzo IP del service provider.
 \param	[in]	port	Porta di ascolto del service provider.
 \return	Risultato dell'esecuzione, \c true in caso di successo e \c false altrimenti.
 \brief		Rimuove dal registro il service provider il cui endpoint è passato come parametro.
*/

/**
 \fn		bool Service_register::add_service (Service_description* s_description)
 \param	[in]	s_description	Descrizione del servizio.
 \return	Risultato dell'esecuzione, \c true in caso di successo e \c false altrimenti.
 \brief		Aggiunge al registro il servizio i cui dati sono passati come parametro.
*/

/**
 \fn		bool Service_register::remove_service (string name, string address, string port)
 \param	[in]	name	Nome del servizio.
 \param	[in]	address	Indirizzo IP del service provider che fornisce il servizio.
 \param	[in]	port	Porta di ascolto del service provider che fornisce il servizio.
 \return	Risultato dell'esecuzione, \c true in caso di successo e \c false altrimenti.
 \brief		Rimuove dal registro il servizio i cui dati sono passati come parametro.
*/

/**
 \fn		Service_description* Service_register::get_service (string required_service_name)
 \param	[in]	name	Nome del servizio da richiedere.
 \return	Descrizione del servizio fornita dal registo e \c NULL se il servizio non è presente nel registro.
 \brief		Ritorna al chiamante la descrizione completa del servizio richiesto.
*/

/**
 \fn		bool Service_register::find_service (string name, string address, string port)
 \param	[in]	name	Nome del servizio da ricercare nel registro.
 \param	[in]	address	Indirizzo IP del service provider che fornisce il servizio.
 \param	[in]	port	Porta di ascolto del service provider che fornisce il servizio.
 \return	Risultato della ricerca, \c true in caso di successo e \c false altrimenti.
 \brief		Ricerca nel registro il servizio le cui informazioni sono passate come parametro.
*/

/**
 \fn		bool Service_register::print_register()
 \return	\c false se il registro è completamente vuoto e \c true altrimenti.
 \brief		Stampa a schermo il registro dei servizi ordinato secondo il nome dei servizi.
*/


//Class Service_register

#ifndef Service_register_H_
#define Service_register_H_

	#include "../../SOA_Library/Types.h"

	#include <map>
	#include <list>
	#include <utility>


	class Service_register {
		private:
			map <string, list<Service_description*> > service_register; ///< Registro dei servizi.
			pthread_mutex_t mutex_1, mutex_2; ///< Semafori per la mutua esclusione nell'accesso corretto al registro.
			int readers_count; ///< Contatore dei lettori attivi.

			void readers_prologue();
			void readers_epilogue();
			void writers_prologue();
			void writers_epilogue();
			
		public:
			Service_register();
			~Service_register();
			
			bool add_service_provider (string address, string port);
			bool remove_service_provider (string address, string port);
			
			bool add_service (Service_description* s_description);
			bool remove_service (string name, string address, string port);
			
			Service_description* get_service (string required_service_name);
			bool find_service (string name, string address, string port);
			bool print_register();
	};

#endif
