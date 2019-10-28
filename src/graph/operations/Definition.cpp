#pragma once
#include<iostream>
#include"Definition.h"

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
	Graph* g = new Graph(this->database->name, name);
	(*this->database->graphMap)[name] = g;
	return g;
}

Schema* Definition::createSchema(string schemaName, string databaseName, string graphName) { return NULL; }
Schema* Definition::createSchema(string name, string graphName){ return NULL; }
void Definition::deleteDatabase(){}
void Definition::deleteSchema(string name, string graphName){}
void Definition::deleteGraph(string name){}

void Definition::loadGraph(string graphName, string databaseName){
	Database* db = Database::getDatabase(databaseName);
	db->cfg->loadConfigFile();
	Graph* g = NULL;
	for (unordered_map<string, Graph*>::iterator it = db->graphMap->begin(); it != db->graphMap->end(); it++) {
		if (it->first == graphName)
			g = it->second;
	}
	if (g == NULL) {
		g = new Graph(databaseName, graphName);
		(*db->graphMap)[graphName] = g;
	}
}

void Definition::loadGraph(string name) {
	if (this->database == NULL)
		return;
	Graph* g = NULL;
	for (unordered_map<string, Graph*>::iterator it = this->database->graphMap->begin(); it != this->database->graphMap->end(); it++) {
		if (it->first == name)
			g = it->second;
	}
	if (g == NULL) {
		g = new Graph(this->database->name, name);
		(*this->database->graphMap)[name] = g;
	}
}
