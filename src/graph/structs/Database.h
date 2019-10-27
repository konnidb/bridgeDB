#pragma once
#include<iostream>
#include"Graph.h"
#include"../../admin/ConfigFile.h"
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Database {
public:
	string name;
	vector<Graph*>* graphVector;
	vector<Schema*>* schemaVector;
	ConfigFileHandler* cfg;
	static Database getDatabase(string name);
	Database();
	~Database(){};

private:
	static unordered_map<string, Database> instances;
	Database(string name);
};