#pragma once
#include<iostream>
#include<fstream>
#include"Edge.h"
using namespace std;

string serializeMap(unordered_map<string, string> properties);
unordered_map<string, string> deserializeMap(string properties);
long char_ptr_to_int(char* c);

SerializableEdge::SerializableEdge() {
	this->objType = EDGE;
}

Serializable* Edge::getSerializable(string path) {
	SerializableEdge* serializable = new SerializableEdge();
	serializable->id = this->id;
	serializable->path = path;
	serializable->properties = this->properties;
	serializable->originNode = this->originNode->id;
	serializable->targetNode = this->targetNode->id;
	return serializable;
}

void SerializableEdge::load(ifstream* streamObj) {
	ifstream* rf;
	if (streamObj == NULL)
		rf = new ifstream(this->path, ios::in | ios::binary);
	else
		rf = streamObj;
	if (!rf) cout << "LOAD: FAILED OPENING" << endl; //ErrorMap::error_loading_object->action();
	/*
	char* id = new char[sizeof(int)];
	rf->read(id, sizeof(int));
	this->id = char_ptr_to_int(id);
	char*  objType = new char[sizeof(int)];
	rf->read(objType, sizeof(int));
	this->objType = (ElementType)char_ptr_to_int(objType);
	string props;
	char* sizec = new char[sizeof(int)];
	rf->read(sizec, sizeof(int));
	long size = char_ptr_to_int(sizec);
	props.resize(size);
	rf->read(&props[0], size);
	this->properties = deserializeMap(props);
	char* schemaId = new char[sizeof(int)];
	rf->read(schemaId, sizeof(int));
	this->schemaId = char_ptr_to_int(schemaId);
	char* originNode = new char[sizeof(int)];
	rf->read(originNode, sizeof(int));
	this->originNode = char_ptr_to_int(originNode);
	char* targetNode = new char[sizeof(int)];
	rf->read(targetNode, sizeof(int));
	this->targetNode = char_ptr_to_int(targetNode);
	*/
	*rf >> this->id;
	long objType;
	*rf >> objType;
	this->objType = (ElementType)objType;
	string props;
	//long size;
	//*rf >> size;
	//props.resize(size);
	*rf >> props;
	this->properties = deserializeMap(props);
	*rf >> this->schemaId;
	*rf >> this->originNode;
	*rf >> this->targetNode;
	if (streamObj == NULL) {
		rf->close();
		if (!rf->good()) cout << "LOAD: FAILED CLOSING" << endl; //ErrorMap::error_loading_object->action();
	}
}

void SerializableEdge::store(ofstream* streamObj) {
	ofstream* wf;
	if (streamObj == NULL)
		wf = new ofstream(this->path, ios::out | ios::binary);
	else
		wf = streamObj;
	if (!wf) cout << "STORE: FAILED OPENING" << endl; //ErrorMap::error_storing_object->action();
	/*wf->write((char *)&this->id, sizeof(int));
	wf->write((char *)&this->objType, sizeof(int));
	string props = serializeMap(this->properties);
	size_t size = props.size();
	wf->write((char *)&size, sizeof(int));
	wf->write(&props[0], size);
	wf->write((char *)&this->schemaId, sizeof(int));
	wf->write((char *)&this->originNode, sizeof(int));
	wf->write((char *)&this->targetNode, sizeof(int));*/
	*wf << this->id;
	long objType = this->objType;
	*wf << objType;
	string props = serializeMap(this->properties);
	//long size;
	//*rf >> size;
	//props.resize(size);
	*wf << props;
	*wf << this->schemaId;
	*wf << this->originNode;
	*wf << this->targetNode;
	if (streamObj == NULL) {
		wf->close();
		if (!wf->good()) cout << "STORE: FAILED CLOSING" << endl; //ErrorMap::error_loading_object->action();
	}
}

Edge::Edge(){}
Edge::Edge(long id, unordered_map<string, string> properties) {
	this->id = id;
	this->properties = properties;
}
Edge::Edge(long id, unordered_map<string, string> properties, Node * originNode, Node * targetNode) {
	this->id = id;
	this->properties = properties;
	this->originNode = originNode;
	this->targetNode = targetNode;
}

Edge::Edge(SerializableEdge serializable) {
	this->id = serializable.id;
	this->properties = serializable.properties;
}

bool Edge::compareEdges(Edge* edge1, Edge* edge2) { //pending more accurate implementation
	if (edge1->id == edge2->id) {
		return true;
	}
	return false;
}

Edge::Edge(long id) {
	this->id = id;
}