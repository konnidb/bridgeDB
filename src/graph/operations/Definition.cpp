#pragma once
#include<iostream>
#include"Definition.h"

using namespace std;

Definition::Definition(Database database){
	this->database = database;
}
Definition::Definition(string database) {
	Database db = Database::getDatabase(database);
	this->database = db;
	db.cfg->loadConfigFile();
}
Database Definition::createDatabase(string name){
	Database db = Database::getDatabase(name);
	db.cfg->loadConfigFile();
	return db;
}
Graph* Definition::createGraph(string graphName, string databaseName){
	Database db = Database::getDatabase(databaseName);
	db.cfg->loadConfigFile();
	Graph* g = new Graph(graphName);
	db.graphVector->push_back(g);
	return g;
}
Graph* Definition::createGraph(string name) {
	Graph* g = new Graph(name);
	this->database.graphVector->push_back(g);
	return g;
}
Schema* Definition::createSchema(string schemaName, string databaseName) {
	Database db = Database::getDatabase(databaseName);
	db.cfg->loadConfigFile();
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
	Database db = Database::getDatabase(databaseName);
	db.cfg->loadConfigFile();
	Graph* g = NULL;
	for (long i = 0; i < (*db.graphVector).size(); i++)
	{
		if (db.graphVector->at(i)->name == graphName)
			g = db.graphVector->at(i);
	}
	if (g == NULL) {
		g = new Graph(graphName);
		(*db.graphVector).push_back(g);
	}
	vector<Node*> nv = g->loadNodeVector();
	vector<Edge*> ev = g->loadEdgeVector(nv);
	g->loadVertexMap(nv, ev);
}

void Definition::loadGraph(string name) {
	Graph* g = NULL;
	for (long i = 0; i < (*this->database.graphVector).size(); i++)
	{
		if (this->database.graphVector->at(i)->name == name)
			g = this->database.graphVector->at(i);
	}
	if (g == NULL) {
		g = new Graph(name);
		(*this->database.graphVector).push_back(g);
	}
	vector<Node*> nv = g->loadNodeVector();
	vector<Edge*> ev = g->loadEdgeVector(nv);
	g->loadVertexMap(nv, ev);
}
