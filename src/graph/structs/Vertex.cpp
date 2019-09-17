#pragma once
#include<iostream>
#include<fstream>
#include"Vertex.h"
using namespace std;

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
	rf->get((char *)&this->id, sizeof(this->id));
	rf->get((char *)&this->objType, sizeof(this->objType));
	rf->get((char *)&this->node, sizeof(this->node));
	size_t size;
	rf->get((char *)&size, sizeof(size));
	for (size_t i = 0; i < size; i++)
	{
		int id;
		rf->get((char *)&id, sizeof(id));
		this->edgesIdVector.push_back(id);
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
	wf->write((char *)&this->id, sizeof(this->id));
	wf->write((char *)&this->objType, sizeof(this->objType));
	wf->write((char *)&this->node, sizeof(this->node));
	size_t size = this->edgesIdVector.size();
	wf->write((char *)&size, sizeof(size));
	for (size_t i = size-1; i >= 0; i--)
	{
		wf->write((char *)&this->edgesIdVector[i], sizeof(this->edgesIdVector[i]));
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