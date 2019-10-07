#pragma once
#include<iostream>
//#include<unordered_map>
#include<string>
#include"..\utils\Serializable.h"
using namespace std;


class Schema : public Serializable {
public:
	long id;
	string name;
	ElementType type;

	Schema();
	Schema(string name, unordered_map<string, string> properties, ElementType type);
	void load(ifstream* streamObj);
	void store(ofstream* streamObj);
};