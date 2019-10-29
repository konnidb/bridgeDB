#pragma once
#include<iostream>
#include<unordered_map>
#include<fstream>
#include<string>
#include <ios>
#include "src/utils/Enums.h"
using namespace std;

string serializeMap(unordered_map<string, string> properties);
unordered_map<string, string> deserializeMap(string properties);
long char_ptr_to_int(char* c);

using namespace std;

class ConfigFileHandler {
public:
	string databaseName;
	unordered_map<ConfigFileAttrbute, string>* configFileMap;

	ConfigFileHandler(string databaseName);
	void loadConfigFile();
	void storeConfigFile();
	void setConfig(ConfigFileAttrbute config, string value);
};