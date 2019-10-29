#include <iostream>
#include"Database.h"
#include "Graph.h"
#include "Schema.h"
#include <vector>
#include <string>
#include <unordered_map>
#include "src/admin/ConfigFile.h"
#include <algorithm>

vector<string> str_to_vector(string input);
string vector_to_str(vector<string> input);
unordered_map<string, Database*>* Database::instances = new unordered_map<string, Database*>();
bool fileExists(string path);
void createSubDir(string dir);
bool dirExists(string dir);

using namespace std;

Database::Database(string name) {
	(*Database::instances)[name] = this;
	this->name = name;
	this->cfg = new ConfigFileHandler(name);
	graphMap = new unordered_map<string,  Graph*>();
}

Database* Database::getDatabase(string name) {
	if (Database::instances->find(name) == Database::instances->end()) {
		Database* d = new Database(name);
	}
	return (*Database::instances)[name];
}

Database::Database(){}

vector<string> Database::getGraphNames() {
	vector<string> graphVector = str_to_vector(this->cfg->configFileMap->at(ConfigFileAttrbute::graphList));
	for (unordered_map<string, Graph*>::iterator it = this->graphMap->begin(); it != this->graphMap->end(); it++) {
		cout << "ITERATING..." << endl;
		if (find(graphVector.begin(), graphVector.end(), it->first) == graphVector.end())
			graphVector.push_back(it->first);
	}
	return graphVector;
}

string Database::buildSotrePath(string graphName, ElementType element, bool createSubDirs) {
	if (!dirExists(this->cfg->configFileMap->at(ConfigFileAttrbute::storeDirectory)))
		throw "Store Directory " + this->cfg->configFileMap->at(ConfigFileAttrbute::storeDirectory) + " doesnt exist!";
	string slash = "/";
#ifdef _WIN32
	slash = "\\";
#endif
	string elementFoder = "";
	switch (element) {
		case ElementType::EDGE:
			elementFoder = "edge";
			break;
		case ElementType::NODE:
			elementFoder = "node";
			break;
		case ElementType::VERTEX:
			elementFoder = "vertex";
			break;
		case ElementType::SCHEMA:
			elementFoder = "schema";
			break;
	}
		string path = this->cfg->configFileMap->at(ConfigFileAttrbute::storeDirectory);
		if (path[path.length() - 1] != slash[0])
			path += slash;
		path += this->name + slash;
		if (createSubDirs)
			createSubDir(path);
		
		path += graphName + slash;
		if (createSubDirs)
			createSubDir(path);

		if (elementFoder.empty())
			cout<< "INVALID ELEMENT" << endl;
		else{
			path += elementFoder + slash;
			if (createSubDirs)
				createSubDir(path);
		}	
		return path;
}