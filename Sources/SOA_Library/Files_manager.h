/**
 \file		Files_manager.h
 \dir		/Source/SOA_Library/
 \date		15/05/2013
 \author	Tamburini Matteo <mattetambu@gmail.com>
 \brief		Funzioni per l'interazione con il file system.
*/

/**
 \fn		string make_client_working_directory (string path)
 \param	[in]	path	Directory di lavoro dei \e Clients all'interno della deve essere creata la directory privata.
 \return	Indice identificativo del \e Client in caso di successo e una stringa vuota altrimenti.
 \brief		Creazione della directory privata del \e Client.
*/

/**
 \fn		bool make_file_list (string path, vector<string> *file_list)
 \param	[in]	path	Directory di cui si richiede la lista di files.
 \param	[out]	file_list	Vettore in cui inserire la lista di files.
 \return	Risultato dell'esecuzione, \c true in caso di successo e \c false altrimenti.
 \brief		Crea una lista dei files presenti nella cartella specificata (tralasciando sottocartelle e files nascosti).
*/

/**
 \fn		bool make_image_from_buffer (string image_path, buffer* image_buffer)
 \param	[in]	image_path	Path relativo all'immagine da realizzare (comprensivo di nome ed estensione del file).
 \param	[in]	image_buffer	Buffer contenente i dati dell'immagine da realizzare.
 \return	Risultato della creazione del file, \c true in caso di successo e \c false altrimenti.
 \brief		Crea un file al path specificato a partire dal buffer passato come parametro.

 Il buffer passato come parametro è utilizzato per dar corpo al file da realizzare che viene creato nella directory
 specificata dall'attributo path (che contiene anche il nome e l'estensione del file da creare)
*/

/**
 \fn		bool get_buffer_from_image (string image_path, buffer* image_buffer)
 \param	[in]	image_path	Path relativo all'immagine da analizzare (comprensivo di nome ed estensione del file).
 \param	[out]	image_buffer	Buffer che dovrà contenere il corpo del file.
 \return	Risultato della lettura del file, \c true in caso di successo e \c false altrimenti.
 \brief		Realizza un buffer a partire dal corpo di un file il cui path è passato come parametro.
 
 I dati relativi alla lettura del file il cui path (che contiene anche il nome e l'estensione del file)
 è passato come parametro sono inseriti all'interno del buffer specificato dal chiamante.
*/


#ifndef Files_manager_H_
#define Files_manager_H_

	#include "Types.h"
	#include <dirent.h>
	#include <sys/stat.h>
	#include <sstream>


	string make_client_working_directory (string path);
	bool make_file_list (string path, vector<string> *file_list);
	bool make_image_from_buffer (string image_path, buffer* image_buffer);
	bool get_buffer_from_image (string image_path, buffer* image_buffer);
	
#endif