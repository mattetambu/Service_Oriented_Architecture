/**
 \file		Store_image.h
 \dir		/Source/Application/Image_storage_server/
 \date		15/05/2013
 \author	Tamburini Matteo <mattetambu@gmail.com>
 \brief		Classe che fornisce il servizio di memorizzazione di un immagine sul server remoto.
*/

/**
 \def		STORE_IMAGE_DIRECTORY
 \brief		Directory di default dello \e Storage_server dove memorizzazione le immagini fornite dai \e Clients.
*/

/** 
 \class		Store_image
 \brief		Classe che fornisce il servizio di memorizzazione di un immagine sul server remoto. E' una classe derivate di \c Service.
*/

/**
 \fn		Store_image::Store_image ()
 \brief		Costruttore di default della classe Store_image.

 Costruttore di default della classe Store_image. Provoca l'inizializzazione dei parametri di ingresso del servizio 
 e setta la directory di lavoro sulla directory default.
*/

/**
 \fn		Store_image::Store_image (string name, string address, string port)
 \param	[in]	name	Nome da assegnare al servizio.
 \param	[in]	address	Indirizzo IP del service provider che fornisce il servizio.
 \param	[in]	port	Porta di ascolto del service provider che fornisce il servizio.
 \brief		Costruttore che inizializza l'istanza della classe Store_image con i parametri forniti.
 
 Costruttore che inizializza l'istanza della classe Store_image con nome, indirizzo e porta forniti in ingresso,
 inizializza i parametri di ingresso del servizio e setta la directory di lavoro sulla directory default. 
*/

/**
 \fn		Store_image::Store_image (string name, string address, string port, string path)
 \param	[in]	name	Nome da assegnare al servizio.
 \param	[in]	address	Indirizzo IP del service provider che fornisce il servizio.
 \param	[in]	port	Porta di ascolto del service provider che fornisce il servizio.
 \param	[in]	path	Directory di lavoro da assegnare al servizio dove salvare i files temporanei.
 \brief		Costruttore che inizializza l'istanza della classe Store_image con i parametri forniti.
 
 Costruttore che inizializza l'istanza della classe Store_image con nome, indirizzo e porta forniti in ingresso,
 inizializza i parametri di ingresso del servizio e imposta la directory di lavoro con il path fornito in ingresso. 
*/

/**
 \fn		Store_image::Store_image (Service_description* s_description)
 \param	[in]	s_description	Descrizione del servizio.
 \brief		Costruttore che inizializza la classe Store_image con le informazioni ottenute dalla descrizione del servizio.
*/

/**
 \fn		Store_image::Store_image (Service_description* s_description, string path)
 \param	[in]	s_description	Descrizione del servizio.
 \param	[in]	path	Directory di lavoro da assegnare al servizio dove salvare i files temporanei.
 \brief		Costruttore che inizializza la classe Store_image con le informazioni ottenute dalla descrizione del servizio
  e imposta la directory di lavoro con il path fornito in ingresso.
*/

/**
 \fn		virtual Store_image::~Store_image ()
 \brief		Distruttore della classe Store_image.
*/

/**
 \fn		Store_image::inizialize_parameters (string path)
 \param	[in]	path	Directory di lavoro da assegnare al servizio dove salvare i files temporanei.
 \brief		Inizializza l'istanza della classe Store_image (è chiamata da ogni costruttore).
 
 Inizializza l'istanza della classe Store_image come segue:
 \li	genera un parametro in ingresso di tipo \c string che conterrà il nome con cui memorizzare l'immagine sul \e Server
 \li	genera un parametro in ingresso di tipo \c buffer atto a mantenere le informazioni relative all'immagine da memorizzare
 \li	crea la directory di lavoro del servizio se questa non esiste
*/

/**
 \fn		bool Store_image::execute ()
 \return	Risultato dell'esecuzione, \c true in caso di successo e \c false altrimenti.
 \brief		Genera una nuova immagine nella directory dello \e Storage_server con nome e dati pari a quelli forniti in ingresso al servizio.
*/


//Class Store_image

#ifndef Store_image_H_
#define Store_image_H_

	#include "../../SOA_Library/Service.h"

	#define STORE_IMAGE_DIRECTORY "./Work_directories/Servers/Image_storage_server/"	
		

	class Store_image : public Service {
		private:
			string path; ///< Directory di lavoro dello \e Storage_server dove memorizzazione le immagini fornite dai \e Clients.
			void inizialize_parameters (string path);
		
		public:
			Store_image ();
			Store_image (string name, string address, string port);
			Store_image (string name, string address, string port, string path);
			Store_image (Service_description* s_description);
			Store_image (Service_description* s_description, string path);
			virtual ~Store_image ();
			
			bool execute ();
	};

#endif
