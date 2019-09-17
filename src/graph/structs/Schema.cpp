#pragma once
#include<iostream>
#include<fstream>
#include"Schema.h"
using namespace std;

string serializeMap(unordered_map<string, string> properties);
unordered_map<string, string> deserializeMap(string properties);

Schema::Schema() {}

Schema::Schema(string name, unordered_map<string, string> properties, ElementType type) {
	this->name = name;
	this->properties = properties;
	this->type = type;
	this->objType = SCHEMA;
}

void Schema::load(ifstream* streamObj) {
	ifstream* rf;
	if (streamObj == NULL)
		rf = new ifstream(this->path, ios::in | ios::binary);
	else
		rf = streamObj;
	if (!rf) cout << "LOAD: FAILED OPENING" << endl; //ErrorMap::error_loading_object->action();
	rf->get((char *)&this->id, sizeof(this->id));
	rf->get((char *)&this->objType, sizeof(this->objType));
	string props;
	size_t size;
	rf->get((char *)&size, sizeof(size));
	props.resize(size);
	rf->get(&props[0], size);
	this->properties = deserializeMap(props);
	rf->get((char *)&this->name, sizeof(this->name));
	rf->get((char *)&this->type, sizeof(this->type));
	if (streamObj == NULL){
		rf->close();
		if (!rf->good()) cout << "LOAD: FAILED CLOSING" << endl; //ErrorMap::error_loading_object->action();
	}
}

void Schema::store(ofstream* streamObj) {
	ofstream* wf;
	if (streamObj == NULL)
		wf = new ofstream(this->path, ios::out | ios::binary);
	else
		wf = streamObj;
	if (!wf) cout << "STORE: FAILED OPENING" << endl; //ErrorMap::error_storing_object->action();
	wf->write((char *)&this->id, sizeof(this->id));
	wf->write((char *)&this->objType, sizeof(this->objType));
	string props = serializeMap(this->properties);
	size_t size = props.size();
	wf->write((char *)&size, sizeof(size));
	wf->write(&props[0], size);
	wf->write((char *)&this->name, sizeof(this->name));
	wf->write((char *)&this->type, sizeof(this->type));
	if (streamObj == NULL) {
		wf->close();
		if (!wf->good()) cout << "STORE: FAILED CLOSING" << endl; //ErrorMap::error_loading_object->action();
	}
}