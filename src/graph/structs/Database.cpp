#include <iostream>
#include"Database.h"
#include "Graph.h"
#include "Schema.h"
#include <vector>
#include <string>
#include <unordered_map>
#include "src/admin/ConfigFile.h"

unordered_map<string, Database> Database::instances;

using namespace std;

Database::Database(string name) {
	this->name = name;
	this->cfg = new ConfigFileHandler(name);
	graphVector = new vector<Graph*>();
	schemaVector = new vector<Schema*>();
	//this->cfg(this->name);
}

Database Database::getDatabase(string name) {
	cout << "shit about to start" << endl;
	if (Database::instances.find(name) == Database::instances.end()) {
		cout << "inside shitty if" << endl;
		Database* d = new Database(name);
		Database::instances[name] = *d;
	}
	cout << "shit has been done" <<endl;
	return Database::instances[name];
}

Database::Database(){}