/**
 \file		Service.h
 \dir		/Source/SOA_Library/
 \date		15/05/2013
 \author	Tamburini Matteo <mattetambu@gmail.com>
 \brief		Classe che contiene la descrizione del servizio, l'elenco dei parametri di ingresso e un'istanza della classe \c Responce.
*/

/** 
 \class		Service
 \brief		Classe che contiene la descrizione del servizio, l'elenco dei parametri di ingresso e un'istanza della classe \c Responce.
*/

/**
 \fn		Service::Service ()
 \brief		Costruttore di default della classe Service.
*/

/**
 \fn		Service::Service (string name, string address, string port)
 \param	[in]	name	Nome del servizio.
 \param	[in]	address	Indirizzo IP del service provider che fornisce il servizio.
 \param	[in]	port	Porta di ascolto del service provider che fornisce il servizio.
 \brief		Costruttore che inizializza la classe Service con i parametri forniti.
*/

/**
 \fn		Service::Service (Service_description* s_description)
 \param	[in]	s_description	Descrizione del servizio.
 \brief		Costruttore che inizializza la classe Service con le informazioni ottenute dalla descrizione del servizio.
*/

/**
 \fn		virtual Service::~Service ()
 \brief		Distruttore della classe Service.
*/

/**
 \fn		void Service::add_parameter (Direction direction, Type type)
 \param	[in]	direction	Direzione del parametro da aggiungere al servizio.
 \param	[in]	type	Tipo del parametro da aggiungere al servizio.
 \brief		Aggiunge un parametro di tipo \e type alla lista dei parametri (di ingresso o uscita) del servizio.
*/

/**
 \fn		bool Service::set_input_parameters (vector<Parameter> parameters)
 \param	[in]	parameters	Vettore di parametri con cui settare i parametri di ingresso del servizio.
 \return	Risultato dell'esecuzione, \c true in caso di successo e \c false altrimenti.
 \brief		Setta i parametri di ingresso del servizio con il valore dei parametri forniti.
*/

/**
 \fn		void Service::set_name (string name)
 \param	[in]	name	Nome del servizio.
 \brief		Setta il nome del servizio con il valore passato come parametro.
*/

/**
 \fn		void Service::set_port (string port)
 \param	[in]	port	Porta su cui è in ascolto il service provider che fornisce il servizio.
 \brief		Setta la porta associata al servizio con il valore passato come parametro.
*/

/**
 \fn		void Service::set_address (string address)
 \param	[in]	address	Indirizzo del service provider che fornisce il servizio.
 \brief		Setta l'indirizzo associato al servizio con il valore passato come parametro.
*/

/**
 \fn		string Service::get_name ()
 \return	Nome del servizio.
 \brief		Ritorna al chiamante il nome del servizio.
*/

/**
 \fn		string Service::get_port ()
 \return	Porta di ascolto del service provider che fornisce il servizio.
 \brief		Ritorna al chiamante la porta associata al servizio.
*/

/**
 \fn		string Service::get_address ()
 \return	Indirizzo del service provider che fornisce il servizio.
 \brief		Ritorna al chiamante l'indirizzo associato al servizio.
*/

/**
 \fn		Service_description* Service::get_description ()
 \return	Descrizione completa del servizio.
 \brief		Ritorna al chiamante la descrizione completa del servizio.
*/

/**
 \fn		bool Service::send_service_request (int* socket)
 \param	[out]	socket	\e Socket sul quale inviare la richiesta di servizio.
 \return	Risultato dell'invio della richiesta, \c true in caso di successo e \c false altrimenti.
 \brief		Invia sul \e Socket la richiesta di servizio al service provider che lo fornisce.
 
 L'invio delle richiesta di servizio avviene nel seguente modo:
 \li	invia il nome del servizio e si pone in attesa dell'accettazione della richiesta
 \li	invia il numero di parametri del servizio e si pone in attesa della conferma
 \li	per ogni parametro invia il tipo e si pone in attesa della conferma
 \li	per ogni parametro invia il valore effettivo del parametro
*/

/**
 \fn		bool Service::receive_service_request (int socket)
 \param	[in]	socket	\e Socket sul quale ricevere la richiesta di servizio.
 \return	Risultato della ricezione della richiesta, \c true in caso di successo e \c false altrimenti.
 \brief		Riceve sul \e Socket la richiesta di servizio da parte del \e Client.
 
 La ricezione delle richiesta di servizio avviene nel seguente modo:
 \li	riceve il nome del servizio richiesto e rifiuta la richiesta se il servizio non viene riconosciuto dal service provider
 \li	riceve il numero di parametri del servizio richiesto e rifiuta la richiesta se il numero non coincide con quello atteso
 \li	per ogni parametro riceve il tipo e rifiuta la richiesta se il tipo non coincide con quello atteso
 \li	per ogni parametro riceve il valore effettivo del parametro
*/

/**
 \fn		bool Service::send_service_responce (int socket)
 \param	[in]	socket	\e Socket sul quale inviare i parametri di risposta del servizio.
 \return	Risultato dell'invio della risposta, \c true in caso di successo e \c false altrimenti.
 \brief		Invia sul \e Socket i parametri di risposta di un servizio chiamando l'omonimo servizio della classe \c Responce.
*/

/**
 \fn		bool Service::receive_service_responce (int socket)
 \param	[in]	socket	\e Socket sul quale ricevere i parametri di risposta del servizio.
 \return	Risultato della ricezione della risposta, \c true in caso di successo e \c false altrimenti.
 \brief		Riceve sul \e Socket i parametri di risposta di un servizio chiamando l'omonimo servizio della classe \c Responce.
*/

/**
 \fn		bool Service::responce_decode (string image_path)
 \param	[in]	image_path	Path relativo all'immagine da realizzare (comprensivo di nome ed estensione del file).
 \return	Risultato della creazione del file, \c true in caso di successo e \c false altrimenti.
 \brief		Crea un file al path specificato a partire dal parametro di risposta del servizio.
*/

/**
 \fn		bool Service::responce_decode (vector<string> *file_list)
 \param	[out]	file_list	Lista di file presenti sul server di storage di immagini.
 \return	Risultato della ricezione della risposta, \c true in caso di successo e \c false altrimenti.
 \brief		Crea la lista dei file presenti sul server di storage (in forma vettoriale) a partire dal parametro di risposta del servizio (tipo stringa).
*/

/**
 \fn		bool virtual execute ()
 \return	Risultato dell'esecuzione, \c true in caso di successo e \c false altrimenti.
 \brief		Funzione che espleta il servizio, da ridefinire nelle classi derivate.
*/


//Class Service

#ifndef Service_H_
#define Service_H_

	#include "./Socket_io.h"
	#include "./Responce.h"
	#include "./Files_manager.h"

	
	class Service {
		protected:
			Service_description s_description; ///< Descrizione del servizio.
			vector<Parameter> parameters; ///< Vettore di tipo \c Parameter che contiene i parametri di ingresso del servizio.
			Responce responce; ///< Istanza della classe \e Responce associata al servizio.
			
		public:
			Service () {}
			Service (string name, string address, string port);
			Service (Service_description* s_description);
			virtual ~Service ();
			
			void add_parameter (Direction direction, Type type);
			bool set_input_parameters (vector<Parameter> parameters);
			
			void set_name (string name);
			void set_port (string port);
			void set_address (string address);
			string get_name ();
			string get_port ();
			string get_address ();
			Service_description* get_description ();
			
			bool send_service_request (int* socket);
			bool receive_service_request (int socket);
			bool send_service_responce (int socket);
			bool receive_service_responce (int socket);
			
			bool virtual responce_decode (string folder_path);
			bool virtual responce_decode (vector<string> *file_list);
			bool virtual execute () { return true; }
	};
	
#endif
