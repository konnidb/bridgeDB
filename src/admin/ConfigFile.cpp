#include<iostream>
#include<unordered_map>
#include<fstream>
#include<string>
#include <ios>
#include "src/utils/Enums.h"
#include"ConfigFile.h"
#include"src/graph/structs/Database.h"
using namespace std;

string serializeMap(unordered_map<string, string> properties);
unordered_map<string, string> deserializeMap(string properties);
long char_ptr_to_int(char* c);
bool fileExists(string path);
vector<string> str_to_vector(string input);
string vector_to_str(vector<string> input);

ConfigFileHandler::ConfigFileHandler(string databaseName) {
	cout << "[ConfigFileHandler] Creating config file" << endl;
	this->databaseName = databaseName;
	this->configFileMap = new unordered_map<ConfigFileAttrbute, string>();
	if (!fileExists(this->databaseName + ".cfg")) {
		cout << "[ConfigFileHandler] Inside if" << endl;
		(*this->configFileMap)[ConfigFileAttrbute::databaseName] = this->databaseName;
		string slash = "/";
#ifdef _WIN32
		slash = "\\";
#endif
		cout << "[ConfigFileHandler] Creating configuration" << endl;
		(*this->configFileMap)[ConfigFileAttrbute::storeDirectory] = "." + slash;
		(*this->configFileMap)[ConfigFileAttrbute::backupDirectory] = "." + slash + this->databaseName + slash + "bkp" + slash;
		(*this->configFileMap)[ConfigFileAttrbute::logDirectory] = "." + slash + "log" + slash;
		(*this->configFileMap)[ConfigFileAttrbute::edgeIndexFile] = "edge.ix";
		(*this->configFileMap)[ConfigFileAttrbute::nodeIndexFile] = "node.ix";
		(*this->configFileMap)[ConfigFileAttrbute::schemaIndexFile] = "schema.ix";
		(*this->configFileMap)[ConfigFileAttrbute::vertexIndexFile] = "vertex.ix";
		(*this->configFileMap)[ConfigFileAttrbute::pageExtension] = ".bdb";
		(*this->configFileMap)[ConfigFileAttrbute::graphList] = "";
	}
	else {
		cout << "[ConfigFileHandler] Loading existing config file" << endl;
		loadConfigFile();
	}
}

void ConfigFileHandler::loadConfigFile() {
	cout << "[ConfigFile] Loading config file..." << endl;
	string path = this->databaseName+".cfg";
	ifstream* rf = new ifstream(path, ios::in | ios::binary);
	if (!rf) cout << "CONFIG FILE: FAILED OPENING" << endl; //ErrorMap::error_loading_object->action();
	string props;
	char* sizec = new char[sizeof(long)];
	cout << "SIZE LONG: " << sizeof(long) << endl;
	cout << "SIZE sizec: " << sizeof(sizec) << endl;

	cout << "[ConfigFile] reading stream" << endl;
	rf->read(sizec, sizeof(long));
	long size = char_ptr_to_int(sizec);
	props.resize(size);
	rf->read(&props[0], size);
	unordered_map<string, string> map = deserializeMap(props);
	for (unordered_map<string, string>::iterator it = map.begin(); it != map.end(); it++) {
		(*this->configFileMap)[(ConfigFileAttrbute)stoi(it->first)] = it->second;
	}
	rf->close();
	if (!rf->good()) cout << "CONFIG FILE: FAILED CLOSING" << endl; //ErrorMap::error_loading_object->action();
}

void ConfigFileHandler::storeConfigFile() {
	string path = this->databaseName+".cfg";
	cout << "OPENING FILE..." << endl;
	ofstream* wf = new ofstream(path, ios::out | ios::binary);
	cout << "FILE OPEN" << endl;
	unordered_map<string, string> map;
	for (unordered_map<ConfigFileAttrbute, string>::iterator it = this->configFileMap->begin(); it != this->configFileMap->end(); it++) {
		if (it->first == ConfigFileAttrbute::graphList) {
			map[to_string(it->first)] = it->second; // vector_to_str(Database::getDatabase(databaseName)->getGraphNames());
		}
		else
			map[to_string(it->first)] = it->second;
	}
	cout << "Iteration Finished" << endl;
	cout << "Serializing init..." << endl;
	string props = serializeMap(map);
	cout << "Map Serialized: " << props << endl;
	long size = props.size();
	cout << "Writing in file..." << endl;	
	wf->write((char*)& size, sizeof(long));
	cout << "WRITED" << endl;
	wf->write(&props[0], size);
	cout << "WRITED" << endl;
	wf->close();
	cout << "File CLOSED..." << endl;
	if (!wf) cout << "CONFIG FILE: FAILED OPENING" << endl; //ErrorMap::error_loading_object->action();
}

void ConfigFileHandler::setConfig(ConfigFileAttrbute config, string value) {
	(*this->configFileMap)[config] = value;
}