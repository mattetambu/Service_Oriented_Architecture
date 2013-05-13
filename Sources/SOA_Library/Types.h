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
