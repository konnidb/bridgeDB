#pragma once
#include<iostream>
#include<unordered_map>
#include<fstream>
#include<string>
#include"Serializable.h"
#include"..\..\utils\LogHandler.h"
using namespace std;


Serializable::Serializable() : objType(UNDEF) {}
Serializable::Serializable(string path) : objType(UNDEF) {
	this->path = path;
}



void Serializable::load() {
	ifstream rf(this->path, ios::out | ios::binary);
	//if (!rf) ErrorMap::error_loading_object->action();
	Serializable deserialized;
	rf.read((char *)&deserialized, sizeof(Serializable));
	rf.close();
	//if (!rf.good()) ErrorMap::error_loading_object->action();
	this->properties = deserialized.properties;
	this->path = deserialized.path;
}

string Serializable::store() {
	ofstream wf(this->path, ios::out | ios::binary);
	//if (!wf) ErrorMap::error_storing_object->action();
	wf.write((char *)this, sizeof(Serializable));
	wf.close();
	//if (!wf.good()) ErrorMap::error_storing_object->action();
	return "";
}
