/**
 \file		Horizontal_flip_image.h
 \dir		/Source/Application/Image_manipulation_server/
 \date		15/05/2013
 \author	Tamburini Matteo <mattetambu@gmail.com>
 \brief		Classe che fornisce il servizio di riflessione di un immagine.
*/

/**
 \def		FLIP_IMAGE_DIRECTORY
 \brief		Directory di lavoro di default dove salvare i files temporanei (immagine sorgente e risultato della riflessione).
*/
 
/**
 \def		REMOVE_IMAGES
 \brief		Se impostata a \c true provoca la rimozione dei files temporanei (immagine sorgente e risultato della riflessione) del \e Server.
*/

/** 
 \class		Horizontal_flip_image
 \brief		Classe che fornisce il servizio di riflessione di un immagine. E' una classe derivate di \c Service.
*/

/**
 \fn		Horizontal_flip_image::Horizontal_flip_image ()
 \brief		Costruttore di default della classe Horizontal_flip_image.

 Costruttore di default della classe Horizontal_flip_image. Provoca l'inizializzazione dei parametri di ingresso e uscita del servizio 
 e setta la directory di lavoro sulla directory default.
*/

/**
 \fn		Horizontal_flip_image::Horizontal_flip_image (string name, string address, string port)
 \param	[in]	name	Nome da assegnare al servizio.
 \param	[in]	address	Indirizzo IP del service provider che fornisce il servizio.
 \param	[in]	port	Porta di ascolto del service provider che fornisce il servizio.
 \brief		Costruttore che inizializza l'istanza della classe Horizontal_flip_image con i parametri forniti.
 
 Costruttore che inizializza l'istanza della classe Horizontal_flip_image con nome, indirizzo e porta forniti in ingresso,
 inizializza i parametri di ingresso e uscita del servizio e setta la directory di lavoro sulla directory default. 
*/

/**
 \fn		Horizontal_flip_image::Horizontal_flip_image (string name, string address, string port, string path)
 \param	[in]	name	Nome da assegnare al servizio.
 \param	[in]	address	Indirizzo IP del service provider che fornisce il servizio.
 \param	[in]	port	Porta di ascolto del service provider che fornisce il servizio.
 \param	[in]	path	Directory di lavoro da assegnare al servizio dove salvare i files temporanei.
 \brief		Costruttore che inizializza l'istanza della classe Horizontal_flip_image con i parametri forniti.
 
 Costruttore che inizializza l'istanza della classe Horizontal_flip_image con nome, indirizzo e porta forniti in ingresso,
 inizializza i parametri di ingresso e uscita del servizio e imposta la directory di lavoro con il path fornito in ingresso. 
*/

/**
 \fn		Horizontal_flip_image::Horizontal_flip_image (Service_description* s_description)
 \param	[in]	s_description	Descrizione del servizio.
 \brief		Costruttore che inizializza la classe Horizontal_flip_image con le informazioni ottenute dalla descrizione del servizio.
*/

/**
 \fn		Horizontal_flip_image::Horizontal_flip_image (Service_description* s_description, string path)
 \param	[in]	s_description	Descrizione del servizio.
 \param	[in]	path	Directory di lavoro da assegnare al servizio dove salvare i files temporanei.
 \brief		Costruttore che inizializza la classe Horizontal_flip_image con le informazioni ottenute dalla descrizione del servizio
  e imposta la directory di lavoro con il path fornito in ingresso.
*/

/**
 \fn		virtual Horizontal_flip_image::~Horizontal_flip_image ()
 \brief		Distruttore della classe Horizontal_flip_image.
*/

/**
 \fn		Horizontal_flip_image::inizialize_parameters (string path)
 \param	[in]	path	Directory di lavoro da assegnare al servizio dove salvare i files temporanei.
 \brief		Inizializza l'istanza della classe Horizontal_flip_image (è chiamata da ogni costruttore).
 
 Inizializza l'istanza della classe Horizontal_flip_image come segue:
 \li	genera un parametro in ingresso di tipo \c buffer atto a mantenere le informazioni relative all'immagine da elaborare
 \li	genera un parametro in uscita di tipo \e buffer per l'immagine riflessa
 \li	crea la directory di lavoro del servizio se questa non esiste
*/

/**
 \fn		bool Horizontal_flip_image::execute ()
 \return	Risultato dell'esecuzione, \c true in caso di successo e \c false altrimenti.
 \brief		Funzione che espleta il servizio di riflessione dell'immagine.
 
 Il servizio di riflessione viene effettuato come segue:
 \li	genera nella directory di lavoro l'immagine da elaborare a partire dal parametro \c buffer in ingresso al servizio
 \li	vi applica l'operatore di riflessione ottenendo una nuova immagine (da ritornare al chiamante)
 \li	compila il parametro di uscita del servizio (di tipo \e buffer) con i dati dell'immagine riflessa
 \li	se \e REMOVE_IMAGES è impostato a \c true, rimuove le due immagini appena create (ormai inutili) dalla directory di lavoro
*/


//Class Horizontal_flip_image

#ifndef Horizontal_flip_image_H_
#define Horizontal_flip_image_H_

	#include "../../SOA_Library/Service.h"
	#include <Magick++.h>
	#include <sstream>

	using namespace Magick;

	#define FLIP_IMAGE_DIRECTORY "./Work_directories/Servers/Image_manipulation_server/Horizontal_flip_image/"
	#define REMOVE_IMAGES true


	class Horizontal_flip_image : public Service {
		private:	
			string path; ///< Directory di lavoro dove salvare i risultati temporanei (immagini sorgente e risultato della riflessione).
			void inizialize_parameters (string path);
		
		public:

			Horizontal_flip_image ();
			Horizontal_flip_image (string name, string address, string port);
			Horizontal_flip_image (string name, string address, string port, string path);
			Horizontal_flip_image (Service_description* s_description);
			Horizontal_flip_image (Service_description* s_description, string path);
			virtual ~Horizontal_flip_image ();
			
			bool execute ();
	};

#endif
