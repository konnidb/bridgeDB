//#pragma once
//#include<iostream>
//#include"../structs/Database.cpp"
//
//using namespace std;
//
//class Definition {
//public:
//	Database database;
//	Definition(Database database){
//		this->database = database;
//	}
//	Definition(string database) {
//		Database db = Database::getDatabase(database);
//		this->database = db;
//		db.cfg->loadConfigFile();
//	}
//	static Database createDatabase(string name){
//		Database db = Database::getDatabase(name);
//		db.cfg->loadConfigFile();
//		return db;
//	}
//	static Graph* createGraph(string graphName, string databaseName){
//		Database db = Database::getDatabase(databaseName);
//		db.cfg->loadConfigFile();
//		Graph* g = new Graph(graphName);
//		db.graphVector.push_back(g);
//		return g;
//	}
//	Graph* createGraph(string name) {
//		Graph* g = new Graph(name);
//		this->database.graphVector.push_back(g);
//		return g;
//	}
//	/*static Schema* createSchema(string schemaName, string databaseName) {
//		Database db = Database::getDatabase(databaseName);
//		db.cfg->loadConfigFile();
//		Schema* s = new Schema(schemaName);
//		db..push_back(s);
//		return s;
//	}
//	Schema createSchema(string name){}*/
//
//	void deleteDatabase(){}
//	void deleteSchema() {}
//	void deleteGraph() {}
//	static void loadGraph(string graphName, string databaseName){
//		Database db = Database::getDatabase(databaseName);
//		db.cfg->loadConfigFile();
//		Graph* g = NULL;
//		for (long i = 0; i < db.graphVector.size(); i++)
//		{
//			if (db.graphVector[i]->name == graphName)
//				g = db.graphVector[i];
//		}
//		if (g == NULL) {
//			g = new Graph(graphName);
//			db.graphVector.push_back(g);
//		}
//		vector<Node*> nv = g->loadNodeVector();
//		vector<Edge*> ev = g->loadEdgeVector(nv);
//		g->loadVertexVector(nv, ev);
//	}
//
//	void loadGraph(string name) {
//		Graph* g = NULL;
//		for (long i = 0; i < this->database.graphVector.size(); i++)
//		{
//			if (this->database.graphVector[i]->name == name)
//				g = this->database.graphVector[i];
//		}
//		if (g == NULL) {
//			g = new Graph(name);
//			this->database.graphVector.push_back(g);
//		}
//		vector<Node*> nv = g->loadNodeVector();
//		vector<Edge*> ev = g->loadEdgeVector(nv);
//		g->loadVertexVector(nv, ev);
//	}
//};
