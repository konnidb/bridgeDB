#pragma once
#include<iostream>
#include"Node.h"
#include<fstream>
using namespace std;

string serializeMap(unordered_map<string, string> properties);
unordered_map<string, string> deserializeMap(string properties);
long char_ptr_to_int(char* c);

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
	/*char o = '1';
	char a = 'a';
	int t = 222;
	cout << "SIZE OF INT: " << sizeof(long) << endl;
	cout << "SIZE OF CHAR: " << sizeof(char) << endl;
	cout << "SIZE OF ID: " << sizeof(this->id) << endl;
	cout << "SIZE OF int 222 to char *: " << sizeof((char*)t) << endl;
	cout << "SIZE OF ID to char *: " << sizeof((char*)this->id) << endl;
	while (o == '1') {
		cout << "CHAR: " <<(long) (unsigned char) a << "    "<< a<< endl;
		rf->read((char*)&a, sizeof(char));
		cin >> o;
	}
	///*/
	char* id = new char[sizeof((char*)this->id)];
	rf->read(id, sizeof(id));
	this->id = char_ptr_to_int(id);
	char*  objType = new char[sizeof(long)];
	rf->read(objType, sizeof(long));
	this->objType = (ElementType) char_ptr_to_int(objType);
	string props;
	char* sizec = new char[sizeof(long)];
	rf->read(sizec, sizeof(long));
	long size = char_ptr_to_int(sizec);
	props.resize(size);
	rf->read(&props[0], size);
	this->properties = deserializeMap(props);
	char* schemaId = new char[sizeof(long)];
	rf->read(schemaId, sizeof(long));
	this->schemaId = char_ptr_to_int(schemaId);
	//cout << "SALE" << endl;
	//*/
	/*
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
	*/
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
	/*
	cout << "SIZE OF long STORE: " << sizeof(long) << endl;
	cout << "TYPE OF long long ID: " << sizeof(this->id) << endl;
	long ff = 2;
	cout << "SIZE OF char id: " << sizeof((char *)&ff) << endl;
	cout << "SIZE OF long id: " << sizeof(this->id) << endl;
	*/
	wf->write((char *)&this->id, sizeof(long));
	wf->write((char *)&this->objType, sizeof(long));
	string props = serializeMap(this->properties);
	long size = props.size();
	wf->write((char *)&size, sizeof(long));
	wf->write(&props[0], size);
	wf->write((char *)&this->schemaId, sizeof(long));
	/*/
	*wf << this->id;
	long objType = this->objType;
	*wf << objType;
	string props = serializeMap(this->properties);
	//long size;
	//*rf >> size;
	//props.resize(size);
	*wf << props;
	*wf << this->schemaId;
	*/
	if (streamObj == NULL) {
		wf->close();
		if (!wf->good()) cout << "NODE STORE: FAILED CLOSING" << endl; //ErrorMap::error_loading_object->action();
	}
}

Node::Node() {

}

Node::Node(long id, unordered_map<string, string> properties) {
	this->id = id;
	this->properties = this->properties;
}

Node::Node(long id) {
	this->id = id;
}

Node::Node(SerializableNode serializable) {
	this->id = serializable.id;
	this->properties = serializable.properties;
}
bool Node::compareNodes(Node* node1, Node* node2) { //pending more accurate implementation
	if (node1->id == node2->id)
		return true;
	return false;
}