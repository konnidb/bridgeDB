#pragma once
#include<iostream>
#include"Node.h"
#include<fstream>
using namespace std;

string serializeMap(unordered_map<string, string> properties);
unordered_map<string, string> deserializeMap(string properties);
int char_ptr_to_int(char* c);

SerializableNode::SerializableNode() {
	this->objType = NODE;
}

Serializable* Node::getSerializable(string path) {
	SerializableNode* serializable = new SerializableNode();
	serializable->path = path;
	serializable->id = this->id;
	serializable->properties = properties;
	return serializable;
}

void SerializableNode::load(ifstream* streamObj) {
	ifstream* rf;
	if (streamObj == NULL)
		rf = new ifstream(this->path, ios::in | ios::binary);
	else
		rf = streamObj;
	if (!rf) cout << "LOAD: FAILED OPENING" << endl; //ErrorMap::error_loading_object->action();
	char* id = new char[sizeof(int)];
	rf->read(id, sizeof(int));
	this->id = char_ptr_to_int(id);
	char*  objType = new char[sizeof(int)];
	rf->read(objType, sizeof(int));
	this->objType = (ElementType) char_ptr_to_int(objType);
	string props;
	char* sizec = new char[sizeof(int)];
	rf->read(sizec, sizeof(int));
	int size = char_ptr_to_int(sizec);
	props.resize(size);
	rf->read(&props[0], size);
	this->properties = deserializeMap(props);
	char* schemaId = new char[sizeof(int)];
	rf->read(schemaId, sizeof(int));
	this->schemaId = char_ptr_to_int(schemaId);
	cout << "SALE" << endl;
	if (streamObj == NULL) {
		rf->close();
		if (!rf->good()) cout << "LOAD: FAILED CLOSING" << endl; //ErrorMap::error_loading_object->action();
	}
}

void SerializableNode::store(ofstream* streamObj) {
	ofstream* wf;
	if (streamObj == NULL)
		wf = new ofstream(this->path, ios::out | ios::binary);
	else
		wf = streamObj;
	if (!wf) cout << "STORE: FAILED OPENING" << endl; //ErrorMap::error_storing_object->action();
	wf->write((char *)&this->id, sizeof(int));
	wf->write((char *)&this->objType, sizeof(int));
	string props = serializeMap(this->properties);
	int size = props.size();
	wf->write((char *)&size, sizeof(int));
	wf->write(&props[0], size);
	wf->write((char *)&this->schemaId, sizeof(int));
	if (streamObj == NULL) {
		wf->close();
		if (!wf->good()) cout << "STORE: FAILED CLOSING" << endl; //ErrorMap::error_loading_object->action();
	}
}

Node::Node() {

}

Node::Node(int id, unordered_map<string, string> properties) {
	this->id = id;
	this->properties = this->properties;
}

Node::Node(int id) {
	this->id = id;
}

Node::Node(SerializableNode serializable) {
	this->id = serializable.id;
	this->properties = this->properties;
}
bool Node::compareNodes(Node* node1, Node* node2) { //pending more accurate implementation
	if (node1->id == node2->id)
		return true;
	return false;
}