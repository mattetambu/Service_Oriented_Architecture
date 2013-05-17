/**
 \file		Threads.h
 \dir		/Source/SOA_Library/
 \date		15/05/2013
 \author	Tamburini Matteo <mattetambu@gmail.com>
 \brief		Classe per la gestione dei threads di servizio e di controllo dei vari \e Servers.
*/

/** 
 \class		Threads
 \brief		Classe per la gestione dei threads di servizio e di controllo dei vari \e Servers.
*/

/**
 \fn		Threads::Threads ()
 \brief		Costruttore della classe Threads. Inizializza il semaforo e la variabile condition e setta il thread come attivo e libero.
*/

/**
 \fn		virtual Threads::~Threads ()
 \brief		Distruttore della classe Threads.
*/

/**
 \fn		bool Threads::test_and_set_busy()
 \return	\c true se il \e thread è stato settato come occupato (era libero al momento della chiamata) e \c false altrimenti.
 \brief		Se il \e thread è libero lo setta come occupato altrimenti non effettua alcuna operazione e ritorna.
*/

/**
 \fn		void Threads::set_busy()
 \brief		Setta il \e thread su occupato.
*/

/**
 \fn		void Threads::set_free()
 \brief		Setta il \e thread su libero.
*/

/**
 \fn		void Threads::set_socket (int client_socket)
 \param	[in]	client_socket	\e Socket per l'interazione con il \e Client.
 \brief		Setta il \e Socket al valore passato come parametro.
*/

/**
 \fn		void Threads::set_ID (pthread_t thread_ID)
 \param	[in]	thread_ID	ID da assegnare al \e thread.
 \brief		Setta l'identificativo del \e thread al valore passato come parametro.
*/

/**
 \fn		int Threads::get_socket ()
 \return	\e Socket associato al \e thread.
 \brief		Ritorna al chiamante il \e socket associato al \e thread.
*/

/**
 \fn		pthread_t Threads::get_ID ()
 \return	\e Identificativo associato al \e thread.
 \brief		Ritorna al chiamante l'ID del \e thread.
*/

/**
 \fn		bool Threads::is_busy()
 \return	\c true se il \e thread è occupato e \c false altrimenti.
 \brief		Verifica se il \e thread è occupato o meno.
*/

/**
 \fn		bool Threads::is_active()
 \return	\c true se il \e thread è attivo e \c false altrimenti.
 \brief		Verifica se il \e thread è attivo o meno.
*/

/**
 \fn		void Threads::wait_start ()
 \brief		Se il \e thread è libero si sospende in attesa dell'invocazione del metodo \c thread_start().
*/

/**
 \fn		void Threads::thread_start ()
 \brief		Attiva il \e thread in attesa per servire una richiesta di un \e Client.
*/

/**
 \fn		void Threads::thread_exit ()
 \brief		Setta il \e thread su occupato e inattivo e lo sveglia per far terminare la sua esecuzione.
*/



//Class Threads

#ifndef Threads_H_
#define Threads_H_

	#include <pthread.h>

	
	class Threads {
		private:	
			bool busy; ///< \e Thread occupato, viene impostato a \c true se il \e thread è stato associato ad un \e Client per rispondere ad una richiesta.
			bool active; ///< \e Thread attivo, viene impostato a \c false per terminare il \e thread.
			int client_socket; ///< \e Socket associato al \e thread per dialogare con il \e Client.
			
			pthread_t thread_ID; ///< Identificativo del \e thread.
			pthread_mutex_t mutex; ///< \e Semaforo per l'accesso in mutua esclusione agli attributi della classe.
			pthread_cond_t condition; ///< \e Condizione utilizzata per sospendere il \e thread in attesa di una richiesta da parte di un \e Client.
			
		public:
			Threads();
			virtual ~Threads();
			
			bool test_and_set_busy();
			void set_busy();
			void set_free();
			void set_socket (int client_socket);
			void set_ID (pthread_t thread_ID);
			
			int get_socket ();
			pthread_t get_ID ();
			
			bool is_busy();
			bool is_active();
			
			void wait_start();
			void thread_start();
			void thread_exit();
	};

#endif