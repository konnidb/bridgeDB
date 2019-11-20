#include<iostream>
#include<fstream>
#include"Vertex.h"
using namespace std;

long char_ptr_to_int(char* c);

SerializableVertex::SerializableVertex() {
	this->objType = VERTEX;
}

//SerializableVertex::~SerializableVertex() {}

SerializableVertex* Vertex::getSerializable(string path) {
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
	if (streamObj == NULL) {
		wf->close();
		if (!wf->good()) cout << "VERTEX STORE: FAILED CLOSING" << endl; //ErrorMap::error_loading_object->action();
	}
}


Vertex::Vertex(){}
Vertex::~Vertex() {
	this->node = NULL;
}
Vertex::Vertex(long id, Node * node) {
	this->id = id;
	this->node = node;
	this->selfDW = NULL;
}

bool Vertex::compare(Vertex* vertex) {
	if (vertex == this || vertex->id == this->id)
		return true;
	bool matchesNodeId = false;
	if(vertex->node!=NULL? vertex->node->id==this->node->id:false)
		matchesNodeId = true;
	bool matchesEdgeIds = true;
	for (long i = 0; i < vertex->edgesVector.size(); i++)
	{
		bool matches = false;
		for (long j = 0; j < this->edgesVector.size(); j++)
		{
			if (vertex->edgesVector[i]->id == this->edgesVector[j]->id) {
				matches = true;
				break;
			}
		}
		if (!matches)
			matchesEdgeIds = false;
	}
	if(matchesEdgeIds && vertex->edgesVector.size()<=0)
		matchesEdgeIds = false;
	if (matchesEdgeIds || matchesNodeId)
		return true;
	return false;
}

DijkstraWrapper* Vertex::getDijkstraWrapper(){
	if (this->selfDW != NULL)
		return selfDW;
	DijkstraWrapper* dw = (DijkstraWrapper*)this;
	dw->weight = NULL;
	dw->previousVertex = NULL;
	this->selfDW = dw;
	return dw;
}

bool Vertex::isEmpty() {
	bool isEmpty = false;
	if (this->node!=NULL?this->node->isEmpty():false)
		isEmpty = true;
	for (long i = 0; i < this->edgesVector.size(); i++)
	{
		if (this->edgesVector[i] != NULL ? this->edgesVector[i]->isEmpty() : false)
			isEmpty = true;
	}
	return isEmpty;
}