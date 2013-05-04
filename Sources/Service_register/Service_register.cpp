//Class Service_register

#include "Service_register.h"


	Service_register::Service_register() {
		pthread_mutex_init (&mutex_1, NULL);
		pthread_mutex_init (&mutex_2, NULL);
		readers_count = 0;
	}
	
	Service_register::~Service_register() {
		map<string, list<Service_description*> >::iterator map_it;
		list<Service_description*>::iterator list_it;
		
		for (map_it = service_register.begin(); map_it != service_register.end(); map_it++) {	
			list_it = (*map_it).second.begin();
			while (list_it != (*map_it).second.end()) list_it = (*map_it).second.erase(list_it);
			(*map_it).second.clear();
		}
		service_register.clear();
	}

	void Service_register::readers_prologue() {
		pthread_mutex_lock (&mutex_1);
		if (++readers_count == 1) pthread_mutex_lock (&mutex_2);
		pthread_mutex_unlock (&mutex_1);
	}
	
	void Service_register::readers_epilogue() {
		pthread_mutex_lock (&mutex_1);
		if (--readers_count == 0) pthread_mutex_unlock (&mutex_2);
		pthread_mutex_unlock (&mutex_1);
	}
	void Service_register::writers_prologue() {
		pthread_mutex_lock (&mutex_2);
	}
	
	void Service_register::writers_epilogue() {
		pthread_mutex_unlock (&mutex_2);
	}
	
	void Service_register::add_service_provider (string address, string port) {
		readers_prologue();	
		// return (already_registered)? false : true;	// TO BE IMPLEMENTED
		readers_epilogue();		
	}
	
	void Service_register::remove_service_provider (string address, string port) {
		writers_prologue();
		
		map<string, list<Service_description*> >::iterator map_it;
		for (map_it = service_register.begin(); map_it != service_register.end(); map_it++) remove_service((*map_it).first, address, port);
		
		writers_epilogue();
	}

	void Service_register::add_service (string name, Service_description* s_description) {
		writers_prologue();
		
		service_register[name].push_front (s_description);
		
		writers_epilogue();
	}
	
	void Service_register::remove_service (string name, string address, string port) {
		writers_prologue();
		
		list<Service_description*>::iterator list_it = service_register[name].begin();
		while (list_it != service_register[name].end())
			if ((*list_it)->address == address && (*list_it)->port == port) list_it = service_register[name].erase(list_it);
			else list_it++;
			
		if (service_register[name].empty()) service_register.erase(name);
		
		writers_epilogue();
	}
	
	Service_description* Service_register::get_service (string required_service_name) {
		writers_prologue();
		
		Service_description* s_description;
		if (service_register[required_service_name].empty()) {
			writers_epilogue();
			return NULL;
		}
		
		list<Service_description*>::iterator list_it = service_register[required_service_name].begin();
		if ((*list_it) != service_register[required_service_name].back()) {
			cout << "Se leggi questo c'è un error";
			service_register[required_service_name].push_back((*list_it));
			service_register[required_service_name].pop_front();
		}
		s_description = (service_register[required_service_name].back());

		writers_epilogue();
		return s_description;
	}
	
	
	void Service_register::print_register() {
		readers_prologue();	
		
		map<string,list<Service_description*> >::iterator map_it;
		list<Service_description*>::iterator list_it;

		cout << endl << endl << "Register:" << endl;
		for (map_it = service_register.begin(); map_it != service_register.end(); map_it++) {
			cout << SPACER << "Service_name: " << (*map_it).first << endl;
			cout << SPACER << SPACER << "Service_providers:" << endl;
			for (list_it = (*map_it).second.begin(); list_it != (*map_it).second.end(); list_it++) {
				cout << SPACER << SPACER << "address: " << (*list_it)->address;		
				cout << SPACER << "port: " << (*list_it)->port << endl;
			}
		}

		readers_epilogue();
	}
