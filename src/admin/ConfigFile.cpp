#pragma once
#include<iostream>
#include<unordered_map>
#include<fstream>
#include<string>
#include"..\utils\Enums.h"
using namespace std;

string serializeMap(unordered_map<string, string> properties);
unordered_map<string, string> deserializeMap(string properties);

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
		ifstream rf(path, ios::in | ios::binary);
		if (!rf) cout << "CONFIG FILE: FAILED OPENING" << endl; //ErrorMap::error_loading_object->action();
		string props;
		size_t size;
		rf.get((char *)&size, sizeof(size));
		props.resize(size);
		rf.get(&props[0], size);
		unordered_map<string, string> map = deserializeMap(props);
		for (unordered_map<string, string>::iterator it = map.begin(); it != map.end(); it++) {
			this->configFileMap[(ConfigFileAttrbute)stoi(it->first)] = it->second;
		}
		rf.close();
		if (!rf.good()) cout << "CONFIG FILE: FAILED CLOSING" << endl; //ErrorMap::error_loading_object->action();
	}

	void storeConfigFile() {
		string path = this->databaseName.append(".cfg");
		ofstream wf(path, ios::out | ios::binary);
		unordered_map<string, string> map;
		for (unordered_map<ConfigFileAttrbute, string>::iterator it = this->configFileMap.begin(); it != this->configFileMap.end(); it++) {
			map[to_string(it->first)] = it->second;
		}
		string props = serializeMap(map);
		size_t size = props.size();
		wf.write((char *)&size, sizeof(size));
		wf.write(&props[0], size);
		if (!wf) cout << "CONFIG FILE: FAILED OPENING" << endl; //ErrorMap::error_loading_object->action();
	}

	void setConfig(string config, string value) {

	}
};