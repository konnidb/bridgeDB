#pragma once
#include<iostream>
#include <string>
#include "../structs/Graph.h"
#include "../structs/Schema.h"
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
	static Schema* createSchema(string schemaName, string databaseName);
	Schema* createSchema(string name);
	void deleteDatabase();
	void deleteSchema();
	void deleteGraph();
	static void loadGraph(string graphName, string databaseName);
	void loadGraph(string name);
};
