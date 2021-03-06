#include <iostream>
#include <string>
#include <unordered_map>
#include "DBHandler.h"
#include "src/graph/structs/Database.h"
#include "src/admin/ConfigFile.h"
#include "src/utils/Enums.h"
#include "src/graph/operations/Definition.h"
#include "src/graph/operations/Manipulation.h"

using namespace std;

DBHandler::DBHandler(Database* db)
{
	this->database = db;
}

DBHandler::DBHandler(string db_name) {
	this->database = Database::getDatabase(db_name);
	cout << db_name << endl;
}

Database* DBHandler::createConfigFile(string db_name, string graph_name) {
	cout << "Looking for db instance" << endl;
    Database* db = Database::getDatabase(db_name);
	ConfigFileHandler* cfgFile = db->cfg;

	cout << "SETTING CONFIG FILE ATTRS" << endl;
    (*cfgFile->configFileMap)[ConfigFileAttrbute::databaseName] = db_name;
	(*cfgFile->configFileMap)[ConfigFileAttrbute::pageExtension] = ".bdb";
	(*cfgFile->configFileMap)[ConfigFileAttrbute::storeDirectory] = "/home/eivazque/bridgeDB/dbs";
	(*cfgFile->configFileMap)[ConfigFileAttrbute::edgeIndexFile] = "edge.ix";
	(*cfgFile->configFileMap)[ConfigFileAttrbute::nodeIndexFile] = "node.ix";
	(*cfgFile->configFileMap)[ConfigFileAttrbute::vertexIndexFile] = "vertex.ix";
	(*cfgFile->configFileMap)[ConfigFileAttrbute::schemaIndexFile] = "schema.ix";
	(*cfgFile->configFileMap)[ConfigFileAttrbute::graphList] = graph_name;
	cfgFile->storeConfigFile();
	return NULL;
}

Manipulation* DBHandler::loadDatabase(string dbName, string graphName) {
	Database* db =  Database::getDatabase(dbName);
	cout << "DB obtained" << endl;
	cout << "DB PATH: " << db->cfg->configFileMap->at(ConfigFileAttrbute::storeDirectory) << endl;
	Definition* def = new Definition(db);
	cout << "Definition created" << endl;
	def->loadGraph(graphName);
	cout << "Load Database completed" << endl;
	return new Manipulation(db->graphMap->at(graphName));
	// cout << "Created Manipulation" << endl;
	// return db;
}

Manipulation* DBHandler::getManipulation(string dbName, string graphName) {
	Database* db = Database::getDatabase(dbName);
	cout << "DB PATH: " << db->cfg->configFileMap->at(ConfigFileAttrbute::storeDirectory) << endl;
	Definition* def = new Definition(db);
	cout << "Definition created" << endl;
	def->loadGraph(graphName);
	cout << "Load Database completed" << endl;
	return new Manipulation(db->graphMap->at(graphName));
}

Database* DBHandler::createDBIfNotExists(string dbName) {
	Database* db = Database::getDatabase(dbName);
	return db;
}

DBHandler::~DBHandler()
{
}
