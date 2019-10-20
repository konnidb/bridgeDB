#pragma once
#include<iostream>
#include<unordered_map>
#include<fstream>
#include<string>
#include <ios>
#include "../utils/Enums.h"
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

	ConfigFileHandler(string databaseName): databaseName(databaseName){};

	void loadConfigFile();

	void storeConfigFile();
	void setConfig(string config, string value);
};