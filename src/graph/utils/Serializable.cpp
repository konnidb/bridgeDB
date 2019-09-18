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

void Serializable::load(ifstream* streamObj) {
	ifstream* rf;
	if (streamObj == NULL)
		rf = new ifstream(this->path, ios::in | ios::binary);
	else
		rf = streamObj;
	if (!rf) cout << "LOAD: FAILED OPENING" << endl; //ErrorMap::error_loading_object->action();
	Serializable deserialized;
	rf->read((char *)&deserialized, sizeof(Serializable));
	if (streamObj == NULL) {
		rf->close();
		if (!rf->good()) cout << "LOAD: FAILED CLOSING" << endl; //ErrorMap::error_loading_object->action();
	}
	this->properties = deserialized.properties;
//	deserialized.deserializeProperties();
	this->path = deserialized.path;
	this->id = deserialized.id;
	this->objType = deserialized.objType;
}

void Serializable::store(ofstream* streamObj) {
	ofstream* wf;
	if (streamObj == NULL)
		wf = new ofstream(this->path, ios::out | ios::binary);
	else
		wf = streamObj;
	if (!wf) cout << "STORE: FAILED OPENING" << endl; //ErrorMap::error_storing_object->action();
	wf->write((char *)&this, sizeof(Serializable));
	if (streamObj == NULL) {
		wf->close();
		if (!wf->good()) cout << "STORE: FAILED CLOSING" << endl; //ErrorMap::error_loading_object->action();
	}
}

Serializable* Element::getSerializable(string path) {
	Serializable* serializable = new Serializable();
	serializable->id = this->id;
	serializable->path = path;
	return serializable;
}


/*
string Serializable::serialize() {
	string serializedObj = "";
	const string propSeparatorChar = "|";
	const string mapSeratorChar = "#";
	const string objSeparatorChar = "~~~~";

	serializedObj.append(to_string(this->id));
	serializedObj.append(propSeparatorChar);
	serializedObj.append(to_string(this->objType));
	serializedObj.append(propSeparatorChar);
	for (unordered_map<string, string>::iterator it = this->properties.begin(); it != this->properties.end(); it++) {
		serializedObj.append(to_string(this->id));
		serializedObj.append(propSeparatorChar);
	}
	return "";
}

void Serializable::setProperties(unordered_map<string, string> properties) {
	for (unordered_map<string, string>::iterator it = properties.begin(); it != properties.end(); it++) {
		const int lk = ((int)it->first.length()+1);
		char* key = new char[lk];
		cout << "SET PROP, KEY SIZE: " << strlen(key) << endl;
		strcpy_s(key, lk, it->first.c_str());
		int lv = ((int)it->second.length()+1);
		char* value = new char[lv];
		strcpy_s(value, lv, it->second.c_str());
		cout << "SET PROP, VAL SIZE: " << sizeof(key) << endl;
		this->properties[key] = value;
	}
}

*/
