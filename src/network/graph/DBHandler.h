#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include "src/graph/structs/Database.h"
#include "src/graph/operations/Manipulation.h"
using namespace std;
class DBHandler
{
private:
    Database* database;
public:
    DBHandler(Database*);
	DBHandler(string);
    static Database* createConfigFile(string);
	static Manipulation* loadDatabase(string, string);
	static Database* createDBIfNotExists(string);
    static Manipulation* getManipulation(string db_name, string graph_name);
    ~DBHandler();
};
