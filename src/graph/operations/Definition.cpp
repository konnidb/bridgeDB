#pragma once
#include<iostream>
#include"Definition.h"

using namespace std;

unordered_map<string, string> deserializeMap(string properties);

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
	Graph* g = Graph::getGraph(databaseName, graphName);
	return g;
}
Graph* Definition::createGraph(string name) {
	if (this->database == NULL)
		return NULL;
	Graph* g = Graph::getGraph(this->database->name, name);
	return g;
}

Schema* Definition::createSchema(string schemaName, string databaseName, string graphName, unordered_map<string, string> properties, ElementType type) {
	Graph* g = Graph::getGraph(databaseName, graphName);
	Schema* s = new Schema(schemaName, properties, type);
	(*g->schemaMap)[s->id] = s;
	return s;
}
Schema* Definition::createSchema(string name, string graphName, unordered_map<string, string> properties, ElementType type) {
	return Definition::createSchema(name, this->database->name, graphName, properties, type);
}
Schema* Definition::createSchema(string schemaName, string databaseName, string graphName, string properties, ElementType type) {
	return Definition::createSchema(schemaName, databaseName, graphName, deserializeMap(properties), type);
}
Schema* Definition::createSchema(string name, string graphName, string properties, ElementType type) {
	return Definition::createSchema(name, this->database->name, graphName, deserializeMap(properties), type);
}
void Definition::deleteDatabase(){}
void Definition::deleteSchema(string name, string graphName){}
void Definition::deleteGraph(string name){}

void Definition::loadGraph(string graphName, string databaseName){
	Database* db = Database::getDatabase(databaseName);
	db->cfg->loadConfigFile();
	Graph* g = Graph::getGraph(databaseName, graphName);
}

void Definition::loadGraph(string name) {
	if (this->database == NULL)
		return;
	Graph* g = Graph::getGraph(this->database->name, name);
}
