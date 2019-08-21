#include<iostream>
#include<unordered_map>
#include<list>
#include<string>
#include"..\..\utils\LogHandler.cpp"
#include"..\utils\Serializable.cpp"
#include"Edge.cpp"
#include"Node.cpp"
using namespace std;

enum SchemaType {
	NODE,
	EDGE,
	GROUP
};

class Schema : Serializable {
public:
	string name;
	SchemaType type;

	//list<int> elements;

	Schema(string name, unordered_map<string, string> properties, SchemaType type): objType(SCHEMA) {
		this->name = name;
		this->properties = properties;
		this->type = type;
	}

};