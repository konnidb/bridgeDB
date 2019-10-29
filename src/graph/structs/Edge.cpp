#include<iostream>
#include<fstream>
#include"Edge.h"
#include <string>
#include <unordered_map>
using namespace std;

string serializeMap(unordered_map<string, string> properties);
unordered_map<string, string> deserializeMap(string properties);
long char_ptr_to_int(char* c);
bool map_contains_values(unordered_map<string, string> properties, unordered_map<string, string> toMatch);

SerializableEdge::SerializableEdge() {
	this->objType = EDGE;
}

//SerializableEdge::~SerializableEdge() {}

Serializable* Edge::getSerializable(string path) {
	SerializableEdge* serializable = new SerializableEdge();
	serializable->id = this->id;
	serializable->path = path;
	serializable->schemaId = this->schema != NULL ? this->schema->id : -1;
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
	char* id = new char[sizeof(long)];
	rf->read(id, sizeof(long));
	this->id = char_ptr_to_int(id);
	char*  objType = new char[sizeof(long)];
	rf->read(objType, sizeof(long));
	this->objType = (ElementType)char_ptr_to_int(objType);
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
	char* originNode = new char[sizeof(long)];
	rf->read(originNode, sizeof(long));
	this->originNode = char_ptr_to_int(originNode);
	char* targetNode = new char[sizeof(long)];
	rf->read(targetNode, sizeof(long));
	this->targetNode = char_ptr_to_int(targetNode);
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
	wf->write((char *)&this->id, sizeof(long));
	wf->write((char *)&this->objType, sizeof(long));
	string props = serializeMap(this->properties);
	long size = props.size();
	wf->write((char *)&size, sizeof(long));
	wf->write(&props[0], size);
	wf->write((char *)&this->schemaId, sizeof(long));
	wf->write((char *)&this->originNode, sizeof(long));
	wf->write((char *)&this->targetNode, sizeof(long));
	if (streamObj == NULL) {
		wf->close();
		if (!wf->good()) cout << "EDGE STORE: FAILED CLOSING" << endl; //ErrorMap::error_loading_object->action();
	}
}

Edge::Edge(){}
Edge::~Edge() {
	this->originNode = NULL;
	this->targetNode = NULL;
}
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
	if (edge1->id == edge2->id)
		return true;
	if (map_contains_values(edge1->properties, edge2->properties))
		return true;
	return false;
}

Edge::Edge(long id) {
	this->id = id;
}

bool Edge::isEmpty() {
	if (this->properties.size() <= 0 && 
		(this->originNode == NULL ? true : this->originNode->isEmpty()) &&
		(this->targetNode == NULL ? true : this->targetNode->isEmpty()))
		return true;
	return false;
}