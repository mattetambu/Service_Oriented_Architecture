/**
 \file		Types.h
 \dir		/Source/SOA_Library/
 \date		15/05/2013
 \author	Tamburini Matteo <mattetambu@gmail.com>
 \brief		Raccolta di definizioni e tipi necessarie all'intero progetto.
*/

/**
 \def		REQUEST_ACCEPTED
 \brief		Costante che un \e Server invia per notificare l'accettazione di una connessione.
*/
 
/**
 \def		REQUEST_NOT_ACCEPTED
 \brief		Costante che un \e Server invia per notificare il rifiuto di una connessione.
*/

/**
 \enum		Type
 
 Enumeratore che rappresenta i quattro tipi di parametro necessari ai servizi (integer, double, string o buffer).
*/

/**
 \var		Type Integer
 \brief		Rappresenta il tipo intero \c integer.
*/

/**
 \var		Type Double
 \brief		Rappresenta il tipo reale \c double.
*/

/**
 \var		Type String
 \brief		Rappresenta il tipo stringa \c string
*/

/**
 \var		Type Buffer
 \brief		Rappresenta il tipo buffer definito nell'omonima struttura.
*/

/**
 \enum		Direction
 
 Enumeratore che la direzione di un parametro di un servizio \c [IN/OUT].
*/

/**
 \var		Direction IN
 \brief		Stabilisce che il parametro è un parametro di ingresso.
*/

/**
 \var		Direction OUT
 \brief		Stabilisce che il parametro è un parametro di uscita.
*/

/**
 \struct	buffer
  \brief	Definizione del tipo buffer.

 Definizione del tipo buffer che contiene il puntatore all'area di memoria (l'effettivo buffer) e la sua dimensione.

 \var		void* pointer
 \var		int size
*/

/**
 \struct	Parameter
 \brief		Valore di un parametro di un servizio.

 Valore di un parametro di un servizio in cui l'attributo \c type definisce il tipo del parametro e
 di conseguenza il campo utile della struttura \c data che ne contiene il valore.

 \var		Type type
 \var		int Integer
 \var		double Double
 \var		string String
 \var		buffer Buffer
*/

/**
 \struct	Parameter_description
 \brief		Descrizione di un parametro di un servizio.
 
 Descrizione di un parametro di un servizio in cui l'attributo \c type definisce il tipo del parametro e \c direction la sua direzione.

 \var		Direction direction
 \var		Type type
*/

/**
 \struct	Service_description
 \brief		Descrizione di un servizio.
 
 Descrizione di un servizio che comprende:
 \li	il nome del servizio
 \li	l'indirizzo del service provider che fornisce il servizio
 \li	la porta di ascolto del service provider che fornisce il servizio
 \li	una descrizione di ogni parametro di ingresso uscita del servizio
 
 \var		string name
 \var		string address
 \var		string port
 \var		vector<Parameter_description> p_description
*/


#ifndef Types_H_
#define Types_H_

	#include <stdio.h>
	#include <stdlib.h>
	#include <iostream>
	#include <string>
	#include <string.h>
	#include <vector>

	using namespace std;


	#define SPACER "   "
	#define REQUEST_NOT_ACCEPTED 0
	#define REQUEST_ACCEPTED 1
	
	
	enum Type {
		Integer,
		Double,
		String,
		Buffer
	};
		
	enum Direction {
		IN,
		OUT
	};

	struct buffer {
		void* pointer;
		int size;
	};

	struct Parameter {
		Type type;
		struct {
			int Integer;
			double Double;
			string String;
			buffer Buffer;
		} data;
	};

	struct Parameter_description {
		Direction direction;
		Type type;	
	};

	struct Service_description {
		string name;
		string address;
		string port;
		vector<Parameter_description> p_description;
	};

#endif
