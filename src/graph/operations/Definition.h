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
	static Schema* createSchema(string schemaName, string databaseName, string graphName, unordered_map<string, string> properties, ElementType type);
	Schema* createSchema(string name, string graphName, unordered_map<string, string> properties, ElementType type);
	static Schema* createSchema(string schemaName, string databaseName, string graphName, string properties, ElementType type);
	Schema* createSchema(string name, string graphName, string properties, ElementType type);
	void deleteDatabase();
	void deleteSchema(string name, string graphName);
	void deleteGraph(string name);
	static void loadGraph(string graphName, string databaseName);
	void loadGraph(string name);
};
