#pragma once
#include<iostream>
#include<unordered_map>
#include"Graph.h"
#include"..\..\admin\ConfigFile.h"
using namespace std;

class Database {
public:
	string name;
	unordered_map<string, Graph*>* graphMap;
	ConfigFileHandler* cfg;
	static Database* getDatabase(string name);
	vector<string> getGraphNames();
	string buildSotrePath(string graphName, ElementType element, bool createSubDir);
	Database();

private:
	static unordered_map<string, Database*> instances;
	Database(string name);
};