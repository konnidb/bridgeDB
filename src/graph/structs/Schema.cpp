#pragma once
#include<iostream>
#include<unordered_map>
#include<string>
//#include"..\..\utils\LogHandler.h"
#include"..\utils\Serializable.h"
using namespace std;

enum SchemaType {
	NODE1,
	EDGE1,
	GROUP
};

class Schema : Serializable {
public:
	string name;
	SchemaType type;

	//list<int> elements;

	Schema(string name, unordered_map<string, string> properties, SchemaType type) {
		this->name = name;
		this->properties = properties;
		this->type = type;
		this->objType = SCHEMA;
	}

};