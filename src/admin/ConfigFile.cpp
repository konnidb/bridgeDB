#include<iostream>
#include<unordered_map>
#include<fstream>
#include<string>
using namespace std;

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
	unordered_map<string, string> configFileMap;

	ConfigFileHandler(string databaseName): databaseName(databaseName){}
	void loadConfigFile() {
		string path = this->databaseName.append(".cfg");
		ifstream rf(path, ios::out | ios::binary);
		if (!rf) cout << "CONFIG FILE: FAILED OPENING" << endl; //ErrorMap::error_loading_object->action();
		rf.read((char *)&this->configFileMap, sizeof(unordered_map<string, string>));
		rf.close();
		if (!rf.good()) cout << "CONFIG FILE: FAILED CLOSING" << endl; //ErrorMap::error_loading_object->action();
	}

	void setConfig(string config, string value) {

	}


};