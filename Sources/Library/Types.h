#ifndef Types_H_
#define Types_H_

#include <iostream>
#include <string>
#include <vector>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

#define SPACER "   "

using namespace std;

	
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
