#include <iostream>
#include <string>
#include <unordered_map>
#include "DBHandler.h"
#include "src/graph/structs/Database.h"
#include "src/admin/ConfigFile.h"
#include "src/utils/Enums.h"

using namespace std;

DBHandler::DBHandler(Database* db)
{
	this->database = db;
}

DBHandler::DBHandler(string db_name) {
	*this->database = Database::getDatabase(db_name);
	cout << db_name << endl;
}

Database DBHandler::createConfigFile(string db_name) {
	cout << "Looking for db instance" << endl;
    Database db = Database::getDatabase(db_name);
	cout << "SETTING CONFIG FILE ATTRS" << endl;
    db.cfg->configFileMap[ConfigFileAttrbute::databaseName] = db_name;
	db.cfg->configFileMap[ConfigFileAttrbute::pageExtension] = ".bdb";
	db.cfg->configFileMap[ConfigFileAttrbute::edgeDirectory] = "~/bridgedb/dbs/" + db_name + "/edge"; // "C:\\Users\\cmarisca\\Documents\\CRISTINA\\proy\\dataTests\\edge\\";
	db.cfg->configFileMap[ConfigFileAttrbute::edgeIndexFile] = "edge.ix";
	db.cfg->configFileMap[ConfigFileAttrbute::nodeDirectory] = "~/bridgedb/dbs/" + db_name + "/node";
	db.cfg->configFileMap[ConfigFileAttrbute::nodeIndexFile] = "node.ix";
	db.cfg->configFileMap[ConfigFileAttrbute::vertexDirectory] = "~/bridgedb/dbs/" + db_name + "/node";
	db.cfg->configFileMap[ConfigFileAttrbute::vertexIndexFile] = "vertex.ix";
	db.cfg->configFileMap[ConfigFileAttrbute::schemaDirectory] = "~/bridgedb/dbs/" + db_name + "/node";
	db.cfg->configFileMap[ConfigFileAttrbute::schemaIndexFile] = "schema.ix";
	db.cfg->storeConfigFile();
	return db;
}

Database DBHandler::loadDatabase(string dbName) {
	return Database::getDatabase(dbName);	
}

Database DBHandler::createDBIfNotExists(string dbName) {
	Database db = Database::getDatabase(dbName);
	return db.graphVector->size() == 0
		? createConfigFile(dbName)
		: loadDatabase(dbName);
}

DBHandler::~DBHandler()
{
}
