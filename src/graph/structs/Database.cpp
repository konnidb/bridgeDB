#include"Database.h"
#include <string>
#include <unordered_map>
#include "src/admin/ConfigFile.h"

unordered_map<string, Database> Database::instances;

Database::Database(string name) {
	this->name = name;
	this->cfg = new ConfigFileHandler(name);
	graphVector = new vector<Graph*>();
	schemaVector = new vector<Schema*>();
	//this->cfg(this->name);
}

Database Database::getDatabase(string name) {
	if (Database::instances.find(name) == Database::instances.end()) {
		Database* d = new Database(name);
		Database::instances[name] = *d;
	}
	return Database::instances[name];
}

Database::Database(){}