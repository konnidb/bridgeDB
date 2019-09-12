#pragma once
#include<iostream>
#include<unordered_map>
#include<fstream>
#include<string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include"Serializable.h"
#include"..\..\utils\LogHandler.h"
using namespace std;


Serializable::Serializable() : objType(UNDEF) {}

void Serializable::load() {
	ifstream rf(this->path, ios::in | ios::binary);
	if (!rf) cout << "LOAD: FAILED OPENING" << endl; //ErrorMap::error_loading_object->action();
	Serializable deserialized;
	rf.read((char *)&deserialized, sizeof(Serializable));
	rf.close();
	if (!rf.good()) cout << "LOAD: FAILED CLOSING" << endl; //ErrorMap::error_loading_object->action();
	cout << "ENTRA LOAD5" << endl;
	this->properties = deserialized.properties;
	cout << "ENTRA LOAD6" << endl;
	this->path = deserialized.path;
	this->id = deserialized.id;
	this->objType = deserialized.objType;
}

string Serializable::store() {
	ofstream wf(this->path, ios::out | ios::binary);
	if (!wf) cout << "STORE: FAILED OPENING" << endl; //ErrorMap::error_storing_object->action();
	wf.write((char *)this, sizeof(Serializable));
	wf.close();
	if (!wf.good()) cout << "STORE: FAILED CLOSING" << endl;  //ErrorMap::error_storing_object->action();
	return "";
}

string serialize() {
	string serializedObj = "";

}

void Serializable::setProperties(unordered_map<string, string> properties) {
	for (unordered_map<string, string>::iterator it = properties.begin(); it != properties.end(); it++) {
		//int lk = ((int)it->first.length()+1);
		char * key = (char *)it->first.c_str();
		for (size_t i = 0; i < sizeof(key)/sizeof(char); i++)
		{
			cout << key[i];
		}
		cout << endl << "LENGHT: " << (sizeof(key) / sizeof(char)) << endl;
		//strcpy_s(key, lk, it->first.c_str());
		//int lv = ((int)it->second.length()+1);
		char * value = (char *)it->second.c_str();
		//strcpy_s(value, lv, it->second.c_str());
		this->properties[key] = value;
	}
}
