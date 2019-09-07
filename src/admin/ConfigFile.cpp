#include<iostream>
#include<unordered_map>
#include<list>
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
	unordered_map<string, string> configFile;

	ConfigFileHandler(string databaseName);
	static void loadConfigFile();
	static void setConfig(string config);


};