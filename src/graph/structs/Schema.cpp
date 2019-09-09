#pragma once
#include<iostream>
#include<unordered_map>
#include<string>
//#include"..\..\utils\LogHandler.h"
#include"..\utils\Serializable.h"
using namespace std;


class Schema : Serializable {
public:
	int id;
	string name;
	ElementType type;

	//list<int> elements;

	Schema(string name, unordered_map<string, string> properties, ElementType type) {
		this->name = name;
		this->properties = properties;
		this->type = type;
		this->objType = SCHEMA;
	}

};