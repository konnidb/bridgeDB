#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include "src/graph/structs/Database.h"
using namespace std;
class DBHandler
{
private:
    Database* database;
public:
    DBHandler(Database*);
	DBHandler(string);
    static Database* createConfigFile(string);
	static Database* loadDatabase(string, string);
	static Database* createDBIfNotExists(string);
    ~DBHandler();
};
