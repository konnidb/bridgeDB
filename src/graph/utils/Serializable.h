#pragma once
#include<iostream>
#include<unordered_map>
#include<string>
#include"..\..\utils\Enums.h"
using namespace std;

class Serializable {
public:
	unordered_map<char*, char*> properties;
	int id;
	string path;
	ElementType objType;

	Serializable();
	void load();
	string store();
	void setProperties(unordered_map<string, string> properties);
};