#pragma once
#include<iostream>
#include<unordered_map>
#include<string>
using namespace std;

enum ElementType {
	NODE,
	EDGE,
	SCHEMA,
	GROUP,
	UNDEF
};

class Serializable {
public:
	unordered_map<string, string> properties;
	int id;
	string path;
	ElementType objType;

	Serializable();
	void load();
	string store();
};