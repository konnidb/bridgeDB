#pragma once
#include<iostream>
#include<unordered_map>
#include<string>
#include"..\..\utils\Enums.h"
using namespace std;

class Serializable {
public:
	unordered_map<string, string> properties;
	int id;
	string path;
	ElementType objType;

	Serializable();
	virtual void load();
	virtual void store();
};
