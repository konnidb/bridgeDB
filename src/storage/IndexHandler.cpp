#pragma once
#include<iostream>
#include<vector>
#include<unordered_map>
#include<fstream>
#include<string>
using namespace std;

string serializeMap(unordered_map<string, string> properties);
unordered_map<string, string> deserializeMap(string properties);
long char_ptr_to_int(char* c);

class Index {
public:
	long id;
	string page;
	long grouperField = NULL;
	long grouperContent = NULL;
};

class IndexHandler {
public:
	string path;
	//vector<Index> indexes;
	unordered_map<string, string> indexMap;
	IndexHandler(string path) {
		this->path = path;
	}

	void loadIndex() {
		ifstream* rf = new ifstream(this->path, ios::in | ios::binary);
		if (!rf) cout << "LOAD: FAILED OPENING" << endl; //ErrorMap::error_loading_object->action();
		string props;
		char* sizec = new char[sizeof(long)];
		rf->read(sizec, sizeof(long));
		long size = char_ptr_to_int(sizec);
		props.resize(size);
		rf->read(&props[0], size);
		this->indexMap = deserializeMap(props);
		rf->close();
		if (!rf->good()) cout << "LOAD: FAILED CLOSING" << endl; //ErrorMap::error_loading_object->action();
	}

	void storeIndex() {
		ofstream* wf = new ofstream(this->path, ios::out | ios::binary);
		if (!wf) cout << "STORE: FAILED OPENING" << endl; //ErrorMap::error_storing_object->action();
		string props = serializeMap(this->indexMap);
		long size = props.size();
		wf->write((char*)& size, sizeof(long));
		wf->write(&props[0], size);
		wf->close();
		if (!wf->good()) cout << "INDEX STORE: FAILED CLOSING" << endl; //ErrorMap::error_loading_object->action();
	}

	long getNextPageId() {
		long max = NULL;
		for (unordered_map<string, string>::iterator it = this->indexMap.begin(); it != this->indexMap.end(); it++) {
			long tmp = stoi(it->second);
			if (max == NULL || max < tmp)
				max = tmp;
		}
		return max == NULL? 1: max + 1;
	}
};