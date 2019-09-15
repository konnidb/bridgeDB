#pragma once
#include<iostream>
#include"Node.h"
#include<fstream>
//#include"..\utils\utils.cpp"
//#include"..\utils\Serializable.h"
using namespace std;

const char ELMNT_SEPARATOR = '~';
const char PROP_SEPARATOR = '¬';

string serializeMap(unordered_map<string, string> properties) {
	string strBuilder = "";
	for (unordered_map<string, string>::iterator it = properties.begin(); it != properties.end(); it++) {
		strBuilder += it->first + ELMNT_SEPARATOR + it->second + PROP_SEPARATOR;
	}
	//cout << "SERIALIZED: " << strBuilder<<endl;
	return strBuilder;
}

unordered_map<string, string> deserializeMap(string properties) {
	unordered_map<string, string> output;
	vector<string> propertiesVector;
	string prop = "";

	for (int i = 0; i < properties.length(); i++)
	{
		if (properties[i] == PROP_SEPARATOR) {
			propertiesVector.push_back(prop);
			prop = "";
		}
		else
			prop += properties[i];
	}


	for (int i = 0; i < propertiesVector.size(); i++)
	{
		string key = "";
		string tmp = "";
		for (int j = 0; j < propertiesVector[i].length(); j++)
		{
			if (propertiesVector[i][j] == ELMNT_SEPARATOR) {
				key = tmp;
				tmp = "";
			}
			else
				tmp += propertiesVector[i][j];
		}
		cout << "key : " << key << " Value: " << tmp;
		output[key] = tmp;
	}
	return output;
}


SerializableNode::SerializableNode() {
	this->objType = NODE;
}

SerializableNode Node::getSerializable() {
	SerializableNode serializable;
	serializable.id = this->id;
	serializable.properties = properties;
	return serializable;
}

void SerializableNode::load() {
	ifstream rf(this->path, ios::in | ios::binary);
	if (!rf) cout << "LOAD: FAILED OPENING" << endl; //ErrorMap::error_loading_object->action();
	SerializableNode deserialized;
	rf.read((char *)&this->id, sizeof(this->id));
	rf.read((char *)&this->objType, sizeof(this->objType));
	string props;
	size_t size;
	rf.read((char *)&size, sizeof(size));
	props.resize(size);
	rf.read(&props[0], size);
	this->properties = deserializeMap(props);
	rf.read((char *)&this->schemaId, sizeof(this->schemaId));
	rf.close();
	if (!rf.good()) cout << "LOAD: FAILED CLOSING" << endl; //ErrorMap::error_loading_object->action();
}

void SerializableNode::store() {
	ofstream wf(this->path, ios::out | ios::binary);
	if (!wf) cout << "STORE: FAILED OPENING" << endl; //ErrorMap::error_storing_object->action();
	wf.write((char *)&this->id, sizeof(this->id));
	wf.write((char *)&this->objType, sizeof(this->objType));
	string props = serializeMap(this->properties);
	size_t size = props.size();
	wf.write((char *)&size, sizeof(size));
	wf.write(&props[0], size);
	wf.write((char *)&this->schemaId, sizeof(this->schemaId));
	wf.close();
}

Node::Node() {

}