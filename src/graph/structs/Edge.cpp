#pragma once
#include<iostream>
#include<fstream>
#include"Edge.h"
using namespace std;

string serializeMap(unordered_map<string, string> properties);
unordered_map<string, string> deserializeMap(string properties);

SerializableEdge::SerializableEdge() {
	this->objType = EDGE;
}

SerializableEdge Edge::getSerializable() {
	SerializableEdge serializable;
	serializable.id = this->id;
	serializable.properties = this->properties;
	serializable.originNode = this->originNode->id;
	serializable.targetNode = this->targetNode->id;
	return serializable;
}

void SerializableEdge::load(ifstream* streamObj) {
	ifstream* rf;
	if (streamObj == NULL)
		rf = new ifstream(this->path, ios::in | ios::binary);
	else
		rf = streamObj;
	if (!rf) cout << "LOAD: FAILED OPENING" << endl; //ErrorMap::error_loading_object->action();
	rf->read((char *)&this->id, sizeof(this->id));
	rf->read((char *)&this->objType, sizeof(this->objType));
	string props;
	size_t size;
	rf->read((char *)&size, sizeof(size));
	props.resize(size);
	rf->read(&props[0], size);
	this->properties = deserializeMap(props);
	rf->read((char *)&this->schemaId, sizeof(this->schemaId));
	rf->read((char *)&this->originNode, sizeof(this->originNode));
	rf->read((char *)&this->targetNode, sizeof(this->targetNode));
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
	wf->write((char *)&this->id, sizeof(this->id));
	wf->write((char *)&this->objType, sizeof(this->objType));
	string props = serializeMap(this->properties);
	size_t size = props.size();
	wf->write((char *)&size, sizeof(size));
	wf->write(&props[0], size);
	wf->write((char *)&this->schemaId, sizeof(this->schemaId));
	wf->write((char *)&this->originNode, sizeof(this->originNode));
	wf->write((char *)&this->targetNode, sizeof(this->targetNode));
	if (streamObj == NULL) {
		wf->close();
		if (!wf->good()) cout << "STORE: FAILED CLOSING" << endl; //ErrorMap::error_loading_object->action();
	}
}