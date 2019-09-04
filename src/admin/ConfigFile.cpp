#include<iostream>
#include<unordered_map>
#include<list>
#include<string>
using namespace std;

class ConfigFileModel {
public:
	string databaseName;
	string dataDirectory;
	string backupDirectory;
	string logDirectory;
};

class ConfigFileHandler {
public:
	string databaseName;

	ConfigFileHandler(string databaseName);

	static unordered_map<string, string> loadConfigFile(string databaseName);

	static unordered_map<string, string> loadConfigFile();

	static bool setConfig(string databaseName, string config);

//	static bool setConfig(string databaseName, string config);
};