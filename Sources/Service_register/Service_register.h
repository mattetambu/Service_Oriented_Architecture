//Classe Service_register

#ifndef Service_register_H_
#define Service_register_H_

#include "../Library/Types.h"
#include "../Library/Service.h"
#include "../Library/Interface.h"
#include "../Library/Socket_io.h"

#include <string>
#include <map>
#include <list>
#include <vector>
#include <utility>
#include <pthread.h>

using namespace std;

class Service_register {
	map <string, list<Service_description*> > service_register;
	pthread_mutex_t mutex_1, mutex_2;
	int readers_count;

 public:
	
	Service_register();
	~Service_register();

	void readers_prologue();
	void readers_epilogue();
	void writers_prologue();
	void writers_epilogue();
	
	void add_service_provider (string address, string port);
	void remove_service_provider (string address, string port);
	
	void add_service (string name, Service_description* s_description);
	void remove_service (string name, string address, string port);
	
	Service_description* get_service (string required_service_name);
	void print_register();
};

#endif
