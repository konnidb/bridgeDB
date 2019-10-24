#include<iostream>
#include"Node.h"
#include "src/graph/utils/Serializable.h"
#include<fstream>
using namespace std;

string serializeMap(unordered_map<string, string> properties);
unordered_map<string, string> deserializeMap(string properties);
long char_ptr_to_int(char* c);
bool map_contains_values(unordered_map<string, string> properties, unordered_map<string, string> toMatch);

SerializableNode::SerializableNode() {
	this->objType = NODE;
}

//SerializableNode::~SerializableNode() {}

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
	wf->write((char *)&this->id, sizeof(long));
	wf->write((char *)&this->objType, sizeof(long));
	string props = serializeMap(this->properties);
	long size = props.size();
	wf->write((char *)&size, sizeof(long));
	wf->write(&props[0], size);
	wf->write((char *)&this->schemaId, sizeof(long));
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
	if (node1->id != NULL && node2->id != NULL){
		if (node1->id == node2->id)
			return true;
	}
	else {
		if (map_contains_values(node1->properties, node2->properties))
			return true;
	}
	return false;
}
bool Node::isEmpty() {
	if (this->properties.size() <= 0)
		return true;
	return false;
}
//Node::~Node() {}