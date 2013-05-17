=============================
Service oriented architecture
=============================

 Progetto:
	Service Oriented Architecture
	
 Autore:
	Tamburini Matteo <mattetambu@gmail.com>
	
 Descrizione: 
	Realizzare un architettura Service Oriented.

 Descrizione dettagliata:
	Il progetto consite nella realizzazione di una architettura Service Oriented.
	E' presente un server che implementa il registro dei servizi a cui i vari service provider registrano i servizi offerti,
	un insieme di due servers che offrono servizi e dei clients che richiedono tali servizi.
 
 	Il registro dei servizi si occupa di registrare i servizi offerti dai vari service provider della rete
		identificando in modo univoco ogni servizio tramite il suo nome e l'endpoint (indirizzo IP e porta) del service provider che lo fornisce.
	
	Il server di manipolazioni delle immagini fornisce i seguenti servizi:
		- rotazione: prende in ingresso un'immagine JPG e la ruota
		- riflessione: prende in ingresso un'immagine JPG e la specchia sull'asse X
		Una volta iscritti nel registro, tali servizi possono essere ottenuti dai client che ne fanno richiesta.
	
	Il server di memorizzazione delle immagini fornisce i seguenti servizi:
		- memorizza immagine: memorizza l'immagine fornita dal client
		- fornisci immagine: restituisce l’immagine richiesta al client
		- fornisci lista: restituisce al client la lista delle immagini memorizzate sul server
		Una volta iscritti nel registro, tali servizi possono essere ottenuti dai client che ne fanno richiesta.
		
	Ogni client esegue ciclicamente le seguenti operazioni:
		- sceglie a caso un'immagine da disco o la richiede al service provider
		- sceglie a caso un servizio di manipolazione da applicare all'immagine (rotazione o riflessione) e lo richiede al server
		- invia il risultato della manipolazione al service provider per il salvataggio.
		Per ottenere i servizi che gli necessitano per prima cosa richiede al server registro l'indirizzo IP e la porta
		dove è possibile trovare i servizi e successivamente contatta i service providers.


 Compilazione dell'applicazione:
	Per la compilazione è presente un makefile quindi è sufficiente eseguire il comando "make".

 Esecuzione dell'applicazione:
	 Per lanciare l'applicazione Service_Oriented_Architecture è necessario eseguire i seguenti quattro file:
		Service_register: Server che fornisce il registro dei servizi
			Comando di esecuzione:
				Service_register_server [Service_register_server_port]
			Parametri
				Service_register_server_port: porta su cui si mette in ascolto il server registro dei servizi

		Image_manipulation_server: Server per la manipolazione delle immagini.
			Comando di esecuzione:
				Image_manipulation_server [Image_manipulation_server_port] [Service_register_server_address] [Service_register_server_port]
			Parametri
				Image_manipulation_server_port: porta su cui si mette in ascolto il server di manipolazione delle immagini
				Service_register_server_address: indirizzo IP del Service_register_server
				Service_register_server_port: porta di ascolto del Service_register_server

		Image_storing_server: Server per la memorizzazione delle immagini.
			Comando di esecuzione:
				Image_storage_server [Image_storage_server_port] [Service_register_server_address] [Service_register_server_port]
			Parametri
				Image_storage_server_port: porta su cui si mette in ascolto il server di memorizzazione delle immagini
				Service_register_server_address: indirizzo IP del Service_register_server
				Service_register_server_port: porta di ascolto del Service_register_server

		Client: Client generico che usufruisce dei servizi.
			Comando di esecuzione:
				Client [Client_iteretions] [Service_register_server_address] [Service_register_server_port]
			Parametri
				Client_iteretions: numero di iterazioni che il Client effettua prima di terminare
				Service_register_server_address: indirizzo IP del Service_register_server
				Service_register_server_port: porta di ascolto del Service_register_server