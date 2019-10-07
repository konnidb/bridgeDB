#pragma once
#include<iostream>
#include<fstream>
#include"Vertex.h"
using namespace std;

long char_ptr_to_int(char* c);

SerializableVertex::SerializableVertex() {
	this->objType = VERTEX;
}

Serializable* Vertex::getSerializable(string path) {
	SerializableVertex* serializable = new SerializableVertex();
	serializable->path = path;
	serializable->id = this->id;
	for (long i = 0; i < (long)this->edgesVector.size(); i++)
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
	//*
	char* id = new char[sizeof(long)];
	rf->read(id, sizeof(long));
	this->id = char_ptr_to_int(id);
	char* objType = new char[sizeof(long)];
	rf->read(objType, sizeof(long));
	this->objType = (ElementType)char_ptr_to_int(objType);
	char* node = new char[sizeof(long)];
	rf->read(node, sizeof(long));
	this->node = char_ptr_to_int(node);
	char* sizec = new char[sizeof(long)];
	rf->read(sizec, sizeof(long));
	long size = char_ptr_to_int(sizec);
	for (long i = 0; i < size; i++)
	{
		char* eIdc = new char[sizeof(long)];
		rf->read(eIdc, sizeof(long));
		long eId = char_ptr_to_int(eIdc);
		this->edgesIdVector.push_back(eId);
	}
	/*/
	*rf >> this->id;
	long objType;
	*rf >> objType;
	this->objType = (ElementType)objType;
	*rf >> this->node;
	long size;
	*rf >> size;
	for (long i = 0; i < size; i++)
	{
		long edge;
		*rf >> edge;
		this->edgesIdVector.push_back(edge);
	}
	*/
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
	//*
	wf->write((char *)&this->id, sizeof(long));
	wf->write((char *)&this->objType, sizeof(long));
	wf->write((char *)&this->node, sizeof(long));
	long size = this->edgesIdVector.size();
	wf->write((char *)&size, sizeof(long));
	for (long i = size-1; i >= 0; i--)
	{
		wf->write((char *)&this->edgesIdVector[i], sizeof(long));
	}
	/*/
	*wf << this->id;
	long objType = this->objType;
	*wf << objType;
	*wf << this->node;
	long size = this->edgesIdVector.size();
	*wf << size;
	for (long i = size - 1; i >= 0; i--)
	{
		*wf << edgesIdVector[i];
	}
	*/
	if (streamObj == NULL) {
		wf->close();
		if (!wf->good()) cout << "VERTEX STORE: FAILED CLOSING" << endl; //ErrorMap::error_loading_object->action();
	}
}


Vertex::Vertex(){}
Vertex::Vertex(long id, Node * node) {
	this->id = id;
	this->node = node;
}