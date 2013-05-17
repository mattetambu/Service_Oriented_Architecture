/**
 \file		Responce.h
 \dir		/Source/SOA_Library/
 \date		15/05/2013
 \author	Tamburini Matteo <mattetambu@gmail.com>
 \brief		Classe che che contiene i parametri di risposta di un servizio.
*/

/** 
 \class		Responce
 \brief		Classe che contiene i parametri di risposta di un servizio (se presenti).
*/

/**
 \fn		Responce::Responce ()
 \brief		Costruttore di default della classe \c Responce.
*/

/**
 \fn		Responce::Responce (Service_description* s_description)
 \param	[in]	s_description	Descrizione del servizio.
 \brief		Costruttore che inizializza la classe \c Responce con le informazioni ottenute dalla descrizione del servizio.
*/

/**
 \fn		virtual Responce::~Responce ()
 \brief		Distruttore della classe \c Responce.
*/

/**
 \fn		void Responce::add_parameter (Type type)
 \param	[in]	type	Tipo del parametro di risposta da aggiungere al servizio.
 \brief		Aggiunge un parametro di tipo \e type alla lista dei parametri di risposta del servizio.
*/

/**
 \fn		bool Responce::set_parameter (int index, Parameter* parameter)
 \param	[in]	index	Indice del parametro di risposta da settare.
 \param	[in]	parameter	Parametro con cui settare il parametro della risposta.
 \return	Risultato dell'esecuzione, \c true in caso di successo e \c false altrimenti.
 \brief		Setta il parametro di indice \c index al valore del parametro \c parameter.
*/

/**
 \fn		bool Responce::get_parameter (int index, Parameter* parameter)
 \param	[in]	index	Indice del parametro di risposta da ritornare al chiamante.
 \param	[out]	parameter	Parametro da ritornare al chiamante.
 \return	Risultato dell'esecuzione, \c true in caso di successo e \c false altrimenti.
 \brief		Ritorna al chiamante il parametro di risposta del servizio di indice \c index.
*/

/**
 \fn		bool Responce::send_service_responce (int socket)
 \param	[in]	socket	\e Socket sul quale inviare i parametri di risposta del servizio.
 \return	Risultato dell'invio della risposta, \c true in caso di successo e \c false altrimenti.
 \brief		Invia sul \e Socket i parametri di risposta di un servizio.
 
 L'invio dei parametri di risposta del servizio avviene nel seguente modo:
 \li	invia il numero di parametri di risposta del servizio e si pone in attesa della conferma
 \li	per ogni parametro invia il tipo e si pone in attesa della conferma
 \li	per ogni parametro invia il valore effettivo del parametro
*/

/**
 \fn		bool Responce::receive_service_responce (int socket)
 \param	[in]	socket	\e Socket sul quale ricevere i parametri di risposta del servizio.
 \return	Risultato della ricezione della risposta, \c true in caso di successo e \c false altrimenti.
 \brief		Riceve sul \e Socket i parametri di risposta di un servizio.
 
 La ricezione dei parametri di risposta del servizio avviene nel seguente modo:
 \li	riceve il numero di parametri di risposta del servizio e se corrispondono con quelli attesi invia la conferma
 \li	per ogni parametro riceve il tipo e lo confronta con quello atteso (e invia il risultato del confronto)
 \li	per ogni parametro riceve il valore effettivo del parametro
*/


//Class Responce

#ifndef Responce_H_
#define Responce_H_

	#include "./Socket_io.h"


	class Responce {
		private:
			vector<Parameter> parameters; ///< Vettore di tipo \c Parameter che contiene i parametri di risposta del servizio.

		public:
			Responce () {}
			Responce (Service_description* s_description);
			virtual ~Responce ();
			
			void add_parameter(Type type);
			bool set_parameter(int index, Parameter* parameter);
			bool get_parameter (int index, Parameter* parameter);
			
			bool send_service_responce (int socket);
			bool receive_service_responce (int socket);
	};

#endif
