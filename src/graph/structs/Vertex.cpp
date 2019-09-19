#pragma once
#include<iostream>
#include<fstream>
#include"Vertex.h"
using namespace std;

int char_ptr_to_int(char* c);

SerializableVertex::SerializableVertex() {
	this->objType = VERTEX;
}

Serializable* Vertex::getSerializable(string path) {
	SerializableVertex* serializable = new SerializableVertex();
	serializable->path = path;
	serializable->id = this->id;
	for (int i = 0; i < (int)this->edgesVector.size(); i++)
	{
		serializable->edgesIdVector.push_back(this->edgesVector[i]->id);
	}
	serializable->node = this->node->id;
	return serializable;
}

void SerializableVertex::load(ifstream* streamObj) {
	ifstream* rf;
	if (streamObj == NULL)
		rf = new ifstream(this->path, ios::in | ios::binary);
	else
		rf = streamObj;
	if (!rf) cout << "LOAD: FAILED OPENING" << endl; //ErrorMap::error_loading_object->action();
	char* id = new char[sizeof(int)];
	rf->read(id, sizeof(int));
	this->id = char_ptr_to_int(id);
	char* objType = new char[sizeof(int)];
	rf->read(objType, sizeof(int));
	this->objType = (ElementType)char_ptr_to_int(objType);
	char* node = new char[sizeof(int)];
	rf->read(node, sizeof(int));
	this->node = char_ptr_to_int(node);
	char* sizec = new char[sizeof(int)];
	rf->read(sizec, sizeof(int));
	int size = char_ptr_to_int(sizec);
	for (int i = 0; i < size; i++)
	{
		char* eIdc = new char[sizeof(int)];
		rf->read(eIdc, sizeof(int));
		int eId = char_ptr_to_int(eIdc);
		this->edgesIdVector.push_back(eId);
	}
	if (streamObj == NULL) {
		rf->close();
		if (!rf->good()) cout << "LOAD: FAILED CLOSING" << endl; //ErrorMap::error_loading_object->action();
	}
}

void SerializableVertex::store(ofstream* streamObj) {
	ofstream* wf;
	if (streamObj == NULL)
		wf = new ofstream(this->path, ios::out | ios::binary);
	else
		wf = streamObj;
	if (!wf) cout << "STORE: FAILED OPENING" << endl; //ErrorMap::error_storing_object->action();
	wf->write((char *)&this->id, sizeof(int));
	wf->write((char *)&this->objType, sizeof(int));
	wf->write((char *)&this->node, sizeof(int));
	int size = this->edgesIdVector.size();
	wf->write((char *)&size, sizeof(int));
	for (int i = size-1; i >= 0; i--)
	{
		wf->write((char *)&this->edgesIdVector[i], sizeof(int));
	}
	if (streamObj == NULL) {
		wf->close();
		if (!wf->good()) cout << "STORE: FAILED CLOSING" << endl; //ErrorMap::error_loading_object->action();
	}
}


Vertex::Vertex(){}
Vertex::Vertex(int id, Node * node) {
	this->id = id;
	this->node = node;
}