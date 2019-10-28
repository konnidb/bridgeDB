#include<iostream>
#include"Definition.h"
#include "src/admin/ConfigFile.h"
#include "../structs/Graph.h"
#include "../structs/Schema.h"
#include "../structs/Database.h"
#include <string>
#include <unordered_map>
#include  <vector>

using namespace std;

Definition::Definition(Database* database){
	this->database = database;
}
Definition::Definition(string database) {
	Database* db = Database::getDatabase(database);
	this->database = db;
	db->cfg->loadConfigFile();
}
Database* Definition::createDatabase(string name){
	Database* db = Database::getDatabase(name);
	db->cfg->loadConfigFile();
	return db;
}
Graph* Definition::createGraph(string graphName, string databaseName){
	Database* db = Database::getDatabase(databaseName);
	db->cfg->loadConfigFile();
	Graph* g = new Graph(databaseName, graphName);
	(*db->graphMap)[graphName]=g;
	return g;
}
Graph* Definition::createGraph(string name) {
	if (this->database == NULL)
		return NULL;
	Graph* g = new Graph("", name);
	(*this->database->graphMap)[name] = g;
	return g;
}
Schema* Definition::createSchema(string schemaName, string databaseName) {
	Database* db = Database::getDatabase(databaseName);
	db->cfg->loadConfigFile();
	//Schema* s = new Schema(schemaName);
	//db.
	return NULL;
}
Schema* Definition::createSchema(string name){
	return NULL;
}
void Definition::deleteDatabase(){}
void Definition::deleteSchema() {}
void Definition::deleteGraph() {}
void Definition::loadGraph(string graphName, string databaseName){
	Database* db = Database::getDatabase(databaseName);
	db->cfg->loadConfigFile();
	Graph* g = NULL;
	if (db->graphMap->find(graphName) != db->graphMap->end()) {
		g = db->graphMap->at(graphName);
	} else {
		g = new Graph(db->name, graphName);
		(*db->graphMap)[graphName] = g;
	}
}

void Definition::loadGraph(string graphName) {
	if (this->database == NULL)
		return;
	Graph* g = NULL;
	if (this->database->graphMap->find(graphName) != this->database->graphMap->end()) {
		g = this->database->graphMap->at(graphName);
	} else {
		g = new Graph(this->database->name, graphName);
		(*this->database->graphMap)[graphName] = g;
	}
}
