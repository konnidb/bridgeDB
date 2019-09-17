#pragma once
#include<iostream>
#include<vector>
#include<unordered_map>
#include<fstream>
#include<string>
using namespace std;

string serializeMap(unordered_map<string, string> properties);
unordered_map<string, string> deserializeMap(string properties);

class Index {
public:
	int id;
	string page;
	int grouperField = NULL;
	int grouperContent = NULL;
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
		string indexesStr;
		size_t size;
		rf->read((char *)&size, sizeof(size));
		indexesStr.resize(size);
		rf->read(&indexesStr[0], size);
		this->indexMap = deserializeMap(indexesStr);
		rf->close();
		if (!rf->good()) cout << "LOAD: FAILED CLOSING" << endl; //ErrorMap::error_loading_object->action();
	}

	void storeIndex() {
		ofstream* wf = new ofstream(this->path, ios::out | ios::binary);
		if (!wf) cout << "STORE: FAILED OPENING" << endl; //ErrorMap::error_storing_object->action();
		string indexesStr = serializeMap(this->indexMap);
		size_t size = indexesStr.size();
		wf->write((char *)&size, sizeof(size));
		wf->write(&indexesStr[0], size);
		wf->close();
		if (!wf->good()) cout << "STORE: FAILED CLOSING" << endl; //ErrorMap::error_loading_object->action();
	}

	int getNextPageId() {
		int max = NULL;
		for (unordered_map<string, string>::iterator it = this->indexMap.begin(); it != this->indexMap.end(); it++) {
			int tmp = stoi(it->second);
			if (max == NULL || max < tmp)
				max = tmp;
		}
		return max == NULL? 1: max + 1;
	}
};