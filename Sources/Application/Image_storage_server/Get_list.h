/**
 \file		Get_list.h
 \dir		/Source/Application/Image_storage_server/
 \date		15/05/2013
 \author	Tamburini Matteo <mattetambu@gmail.com>
 \brief		Classe che fornisce la lista dei files presenti sul server remoto.
*/

/**
 \def		GET_LIST_DIRECTORY
 \brief		Directory di default dello \e Storage_server dove ricercare le immagini con cui creare la lista.
*/

/** 
 \class		Get_list
 \brief		Classe che fornisce la lista dei files presenti sul server remoto. E' una classe derivate di \c Service.
*/

/**
 \fn		Get_list::Get_list ()
 \brief		Costruttore di default della classe Get_list.

 Costruttore di default della classe Get_list. Provoca l'inizializzazione dei parametri di ingresso e uscita del servizio 
 e setta la directory di lavoro sulla directory default.
*/

/**
 \fn		Get_list::Get_list (string name, string address, string port)
 \param	[in]	name	Nome da assegnare al servizio.
 \param	[in]	address	Indirizzo IP del service provider che fornisce il servizio.
 \param	[in]	port	Porta di ascolto del service provider che fornisce il servizio.
 \brief		Costruttore che inizializza l'istanza della classe Get_list con i parametri forniti.
 
 Costruttore che inizializza l'istanza della classe Get_list con nome, indirizzo e porta forniti in ingresso,
 inizializza i parametri di ingresso e uscita del servizio e setta la directory di lavoro sulla directory default. 
*/

/**
 \fn		Get_list::Get_list (string name, string address, string port, string path)
 \param	[in]	name	Nome da assegnare al servizio.
 \param	[in]	address	Indirizzo IP del service provider che fornisce il servizio.
 \param	[in]	port	Porta di ascolto del service provider che fornisce il servizio.
 \param	[in]	path	Directory di lavoro dove ricercare i files per creare la lista.
 \brief		Costruttore che inizializza l'istanza della classe Get_list con i parametri forniti.
 
 Costruttore che inizializza l'istanza della classe Get_list con nome, indirizzo e porta forniti in ingresso,
 inizializza i parametri di ingresso e uscita del servizio e imposta la directory di lavoro con il path fornito in ingresso. 
*/

/**
 \fn		Get_list::Get_list (Service_description* s_description)
 \param	[in]	s_description	Descrizione del servizio.
 \brief		Costruttore che inizializza la classe Get_list con le informazioni ottenute dalla descrizione del servizio.
*/

/**
 \fn		Get_list::Get_list (Service_description* s_description, string path)
 \param	[in]	s_description	Descrizione del servizio.
 \param	[in]	path	Directory di lavoro dove ricercare i files per creare la lista.
 \brief		Costruttore che inizializza la classe Get_list con le informazioni ottenute dalla descrizione del servizio
  e imposta la directory di lavoro con il path fornito in ingresso.
*/

/**
 \fn		virtual Get_list::~Get_list ()
 \brief		Distruttore della classe Get_list.
*/

/**
 \fn		Get_list::inizialize_parameters (string path)
 \param	[in]	path	Directory di lavoro dove ricercare i files per creare la lista.
 \brief		Inizializza l'istanza della classe Get_list (è chiamata da ogni costruttore).
 
 Inizializza l'istanza della classe Get_list come segue:
 \li	genera un parametro in uscita di tipo \c string che conterrà la lista dei files presenti sul server remoto
 \li	crea la directory di lavoro del servizio se questa non esiste
*/

/**
 \fn		bool Get_list::execute ()
 \return	Risultato dell'esecuzione, \c true in caso di successo e \c false altrimenti.
 \brief		Genera la lista dei files presenti nella directory di lavoro del \e Server e con questa compila il parametro di uscita del servizio.
*/


//Class Get_list

#ifndef Get_list_H_
#define Get_list_H_

	#include "../../SOA_Library/Service.h"

	#define GET_LIST_DIRECTORY "./Work_directories/Servers/Image_storage_server/"	
		

	class Get_list : public Service{
		private:
			string path; ///< Directory di lavoro dello \e Storage_server dove ricercare le immagini con cui creare la lista.
			void inizialize_parameters (string path);
		
		public:
			Get_list ();
			Get_list (string name, string address, string port);
			Get_list (string name, string address, string port, string path);
			Get_list (Service_description* s_description);
			Get_list (Service_description* s_description, string path);
			virtual ~Get_list ();
				
			bool execute ();
	};

#endif
