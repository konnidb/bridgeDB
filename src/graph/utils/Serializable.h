#pragma once
#include<iostream>
#include<unordered_map>
#include<string>
using namespace std;

enum ElementType {
	NODE,
	EDGE,
	SCHEMA,
	UNDEF
};

class Serializable {
public:
	unordered_map<string, string> properties;
	int id;
	string path;
	ElementType objType;

	Serializable();
	Serializable(string path);

	void load(string contentStr);

	string store();
};