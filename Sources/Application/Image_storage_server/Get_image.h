/**
 \file		Get_image.h
 \dir		/Source/Application/Image_storage_server/
 \date		15/05/2013
 \author	Tamburini Matteo <mattetambu@gmail.com>
 \brief		Classe che fornisce al richiedente un'immagine presente sul server remoto.
*/

/**
 \def		GET_IMAGE_DIRECTORY
 \brief		Directory di default dello \e Storage_server dove ricercare le immagini da fornire ai \e Clients.
*/

/** 
 \class		Get_image
 \brief		Classe che fornisce al richiedente un'immagine presente sul server remoto. E' una classe derivate di \c Service.
*/

/**
 \fn		Get_image::Get_image ()
 \brief		Costruttore di default della classe Get_image.

 Costruttore di default della classe Get_image. Provoca l'inizializzazione dei parametri di ingresso e uscita del servizio 
 e setta la directory di lavoro sulla directory default.
*/

/**
 \fn		Get_image::Get_image (string name, string address, string port)
 \param	[in]	name	Nome da assegnare al servizio.
 \param	[in]	address	Indirizzo IP del service provider che fornisce il servizio.
 \param	[in]	port	Porta di ascolto del service provider che fornisce il servizio.
 \brief		Costruttore che inizializza l'istanza della classe Get_image con i parametri forniti.
 
 Costruttore che inizializza l'istanza della classe Get_image con nome, indirizzo e porta forniti in ingresso,
 inizializza i parametri di ingresso e uscita del servizio e setta la directory di lavoro sulla directory default. 
*/

/**
 \fn		Get_image::Get_image (string name, string address, string port, string path)
 \param	[in]	name	Nome da assegnare al servizio.
 \param	[in]	address	Indirizzo IP del service provider che fornisce il servizio.
 \param	[in]	port	Porta di ascolto del service provider che fornisce il servizio.
 \param	[in]	path	Directory di lavoro dove ricercare i files per creare la lista.
 \brief		Costruttore che inizializza l'istanza della classe Get_image con i parametri forniti.
 
 Costruttore che inizializza l'istanza della classe Get_image con nome, indirizzo e porta forniti in ingresso,
 inizializza i parametri di ingresso e uscita del servizio e imposta la directory di lavoro con il path fornito in ingresso. 
*/

/**
 \fn		Get_image::Get_image (Service_description* s_description)
 \param	[in]	s_description	Descrizione del servizio.
 \brief		Costruttore che inizializza la classe Get_image con le informazioni ottenute dalla descrizione del servizio.
*/

/**
 \fn		Get_image::Get_image (Service_description* s_description, string path)
 \param	[in]	s_description	Descrizione del servizio.
 \param	[in]	path	Directory di lavoro dove ricercare i files per creare la lista.
 \brief		Costruttore che inizializza la classe Get_image con le informazioni ottenute dalla descrizione del servizio
  e imposta la directory di lavoro con il path fornito in ingresso.
*/

/**
 \fn		virtual Get_image::~Get_image ()
 \brief		Distruttore della classe Get_image.
*/

/**
 \fn		Get_image::inizialize_parameters (string path)
 \param	[in]	path	Directory di lavoro dove ricercare i files per creare la lista.
 \brief		Inizializza l'istanza della classe Get_image (è chiamata da ogni costruttore).
 
 Inizializza l'istanza della classe Get_image come segue:
 \li	genera un parametro in ingresso di tipo \c string che conterrà il nome dell'immagine da richiedere al server remoto
 \li	genera un parametro in uscita di tipo \e buffer per l'immagine da inviare al \e Client
 \li	crea la directory di lavoro del servizio se questa non esiste
*/

/**
 \fn		bool Get_image::execute ()
 \return	Risultato dell'esecuzione, \c true in caso di successo e \c false altrimenti.
 \brief		Compila il parametro di uscita del servizio con l'immagine richiesta dal chiamante (se presente).
*/


//Class Get_image

#ifndef Get_image_H_
#define Get_image_H_

	#include "../../SOA_Library/Service.h"

	#define GET_IMAGE_DIRECTORY "./Work_directories/Servers/Image_storage_server/"	
		

	class Get_image: public Service {
		private:
			string path; ///< Directory di lavoro dello \e Storage_server dove ricercare le immagini da fornire ai \e Clients.
			void inizialize_parameters (string path);
		
		public:
			Get_image ();
			Get_image (string name, string address, string port);
			Get_image (string name, string address, string port, string path);
			Get_image (Service_description* s_description);
			Get_image (Service_description* s_description, string path);
			virtual ~Get_image ();
			
			bool execute ();
	};

#endif
