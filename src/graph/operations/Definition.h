#pragma once
#include<iostream>
#include"../structs/Database.h"

using namespace std;

class Definition {
public:
	Database* database;
	Definition(Database* database);
	Definition(string database);
	static Database* createDatabase(string name);
	static Graph* createGraph(string graphName, string databaseName);
	Graph* createGraph(string name);
	static Schema* createSchema(string schemaName, string databaseName, string graphName);
	Schema* createSchema(string name, string graphName);
	void deleteDatabase();
	void deleteSchema(string name, string graphName);
	void deleteGraph(string name);
	static void loadGraph(string graphName, string databaseName);
	void loadGraph(string name);
};
