#pragma once
#include<iostream>
#include<unordered_map>
#include<string>
//#include"..\..\utils\LogHandler.h"
#include"..\utils\Serializable.h"
using namespace std;


class Schema : public Serializable {
public:
	int id;
	string name;
	ElementType type;

	Schema(){}

	Schema(string name, unordered_map<string, string> properties, ElementType type) {
		this->name = name;
		this->properties = properties;
		this->type = type;
		this->objType = SCHEMA;
	}

	void load(){}
	void store(){}
};