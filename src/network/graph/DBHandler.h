#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include "src/graph/structs/Database.h"
#include "src/graph/operations/Definition.h"
using namespace std;
class DBHandler
{
private:
    Database* database;
public:
    DBHandler(Database*);
	DBHandler(string);
    Database createConfigFile(string);
	Database loadDatabase(string);
	Database createDBIfNotExists(string);
    ~DBHandler();
};
