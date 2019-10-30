#pragma once
#include<iostream>
#include<unordered_map>
#include<string>
#include"src/utils/Enums.h"
using namespace std;

class Serializable {
public:
	unordered_map<string, string> properties;
	long id;
	string path;
	ElementType objType;

	Serializable();
	virtual void load(ifstream* streamObj);
	virtual void store(ofstream* streamObj);
};


class Element {
public:
	long id;
	virtual Serializable* getSerializable(string path);
};
