#pragma once
#include<iostream>
#include<unordered_map>
#include<fstream>
#include"..\utils\Enums.h"

using namespace std;

class ConfigFileHandler {
public:
	string databaseName;
	unordered_map<ConfigFileAttrbute, string> configFileMap;

	ConfigFileHandler(string databaseName);
	void loadConfigFile();
	void storeConfigFile();
	void setConfig(ConfigFileAttrbute config, string value);
};