#pragma once
#include<iostream>
#include<unordered_map>
#include<fstream>
#include<string>
#include"..\utils\Enums.h"
using namespace std;

string serializeMap(unordered_map<string, string> properties);
unordered_map<string, string> deserializeMap(string properties);
long char_ptr_to_int(char* c);

class ConfigFileModel {
public:
	string databaseName;
	string dataDirectory;
	string nodeIndexDirectory;
	string edgeIndexDirectory;
	string backupDirectory;
	string logDirectory;
};

class ConfigFileHandler {
public:
	string databaseName;
	unordered_map<ConfigFileAttrbute, string> configFileMap;

	ConfigFileHandler(string databaseName): databaseName(databaseName){}

	void loadConfigFile() {
		string path = this->databaseName.append(".cfg");
		ifstream* rf = new ifstream(path, ios::in | ios::binary);
		if (!rf) cout << "CONFIG FILE: FAILED OPENING" << endl; //ErrorMap::error_loading_object->action();
		string props;
		char* sizec = new char[sizeof(long)];
		cout << "SIZE LONG: " << sizeof(long) << endl;
		cout << "SIZE sizec: " << sizeof(sizec) << endl;
		rf->read(sizec, sizeof(long));
		long size = char_ptr_to_int(sizec);
		props.resize(size);
		rf->read(&props[0], size);
		unordered_map<string, string> map = deserializeMap(props);
		for (unordered_map<string, string>::iterator it = map.begin(); it != map.end(); it++) {
			this->configFileMap[(ConfigFileAttrbute)stoi(it->first)] = it->second;
		}
		rf->close();
		if (!rf->good()) cout << "CONFIG FILE: FAILED CLOSING" << endl; //ErrorMap::error_loading_object->action();
	}

	void storeConfigFile() {
		string path = this->databaseName.append(".cfg");
		ofstream* wf = new ofstream(path, ios::out | ios::binary);
		unordered_map<string, string> map;
		for (unordered_map<ConfigFileAttrbute, string>::iterator it = this->configFileMap.begin(); it != this->configFileMap.end(); it++) {
			map[to_string(it->first)] = it->second;
		}
		string props = serializeMap(map);
		long size = props.size();
		wf->write((char*)& size, sizeof(long));
		wf->write(&props[0], size);
		wf->close();
		if (!wf) cout << "CONFIG FILE: FAILED OPENING" << endl; //ErrorMap::error_loading_object->action();
	}

	void setConfig(string config, string value) {

	}
};