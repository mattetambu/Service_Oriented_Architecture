#include "Threads.h"

	Threads::Threads() {
		busy = false;
		active = true;
		
		pthread_cond_init (&condition, NULL);
		pthread_mutex_init (&mutex, NULL);
	}
	
	Threads::~Threads() {}
	
	bool Threads::test_and_set_busy () {
		if (busy) return false;
		
		pthread_mutex_lock (&mutex);
		busy = true;
		pthread_mutex_unlock (&mutex);
		return true;
	}
	
	void Threads::set_busy() {
		pthread_mutex_lock (&mutex);
		busy = true;
		pthread_mutex_unlock (&mutex);
	}
	
	void Threads::set_free() {
		pthread_mutex_lock (&mutex);
		busy = false;
		pthread_mutex_unlock (&mutex);
	}

	void Threads::set_socket (int client_socket) {
		pthread_mutex_lock (&mutex);
		(*this).client_socket = client_socket;
		pthread_mutex_unlock (&mutex);
	}
	
	void Threads::set_ID (pthread_t thread_ID){
		pthread_mutex_lock (&mutex);
		(*this).thread_ID = thread_ID;
		pthread_mutex_unlock (&mutex);
	}
		
	int Threads::get_socket () {
		return client_socket;
	}

	pthread_t Threads::get_ID () {
		return thread_ID;
	}

	bool Threads::is_busy() {
		return busy;
	}
	
	bool Threads::is_active() {
		return active;
	}
	
	void Threads::wait_start() {
		pthread_mutex_lock (&mutex);
		while (!busy) pthread_cond_wait(&condition, &mutex);
		pthread_mutex_unlock (&mutex);
	}
	
	void Threads::thread_start() {
		pthread_cond_signal(&condition);
	}
	
	void Threads::thread_exit() {
		pthread_mutex_lock (&mutex);
		busy = true;
		active = false;
		pthread_mutex_unlock (&mutex);
		pthread_cond_signal(&condition);
	}
