#pragma once
#include<iostream>
#include<unordered_map>
//#include"..\utils\dependencies\json.hpp"
#include<string>
#include"..\graph\structs\Node.h"
#include"..\graph\structs\Edge.h"
//#include"..\graph\structs\Vertex.h"
#include"..\graph\structs\Database.h"
#include"..\utils\Enums.h"
#include"..\graph\operations\Manipulation.h"
#include"..\graph\operations\Definition.h"

using namespace std;

string gen_random(const long len) {
	string s;
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";
	s.resize(len);
	for (long i = 0; i < len; ++i) {
		s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
	}
	return s;
}

void generates_semi_random_graph(string dbname) {
	long id = 1;
	Database* db = Database::getDatabase(dbname);
	cout << "CONFIG EDGE DIR: " << db->buildSotrePath(dbname, ElementType::EDGE, false) << endl;
	Definition* d = new Definition(db);
	d->createGraph("testGraph");
	Graph* g = db->graphMap->at("testGraph");
	g->id = id++;
	Schema* s1 = new Schema();
	s1->id = id++;
	s1->name = "persona";
	s1->type = ElementType::NODE;
	unordered_map<string, string> properties;
	properties["nombre"] = to_string(DataType::STR_);
	properties["edad"] = to_string(DataType::NUM_);
	properties["telefono"] = to_string(DataType::STR_);
	properties["correo"] = to_string(DataType::STR_);
	properties["pw"] = to_string(DataType::STR_);
	s1->properties = properties;
	(*g->schemaMap)[s1->id] = s1;
	vector<Node*> nodeVec;

	int nodeId = 0;
	int edgeId = 0;
	int vertexId = 0;
	for (long i = 0; i < 16; i++)
	{
		Node* n = new Node();
		n->id = nodeId++;
		for (unordered_map<string, string>::iterator it = properties.begin(); it != properties.end(); it++)
		{
			if (it->second == to_string(DataType::NUM_))
				n->properties[it->first] = to_string((rand() % 1000000000) + 1000000000);
			else
				n->properties[it->first] = gen_random(10);
		}
		n->schema = s1;
		Vertex* v = new Vertex();
		v->id = vertexId++;
		v->node = n;
		nodeVec.push_back(n);
		g->vertexMap->insert({ n, v });
	}
	int count = 0;
	for (unordered_map<Node*, Vertex*>::iterator it = g->vertexMap->begin(); it != g->vertexMap->end(); it++) {
		{
			for (long j = count; j < count+3 && j < nodeVec.size(); j++)
			{
				Edge* e = new Edge();
				e->id = edgeId++;
				e->properties["t"] = to_string((rand() % 20) + 0);
				e->originNode = it->first;
				e->targetNode = nodeVec[j];
				it->second->edgesVector.push_back(e);
			}
			count++;
		}
	}
		cout << "holi" << endl;
		g->storeVertexMap();
		g->storeSchemaMap();
		db->cfg->storeConfigFile();
}

void load_graph_test(string dbname) {
	Database* db = Database::getDatabase(dbname);
	if(db->cfg->configFileMap->size()==0)
		db->cfg->loadConfigFile();
	cout << "CONFIG EDGE DIR: " << db->buildSotrePath(dbname, ElementType::EDGE, false) << endl;
	Graph* g = Graph::getGraph(db->name, dbname);
	(*db->graphMap)[dbname] = g;
	vector<Node*> nv = g->loadNodeVector();
	vector<Edge*> ev = g->loadEdgeVector(nv);
	g->loadVertexMap(nv, ev);
}

string getSimpleNodesJson(string dbname){
	Database* db = Database::getDatabase(dbname);
	string output= "";
	for (unordered_map<Node*, Vertex*>::iterator it = db->graphMap->at(dbname)->vertexMap->begin(); it != db->graphMap->at(dbname)->vertexMap->end(); it++) {
		string name = to_string(it->first->id);//it->first->properties["nombre"]
		if (output.empty()) {
			output = "[";
			output += "{ \"name\": \"" + name + "\" }";// , \"group\":  " + it->first->properties["group"] + " }";
		}else
			output += ",{ \"name\": \"" + name + "\" }";// , \"group\": " + it->first->properties["group"] + " }";
	}
	if(!output.empty()) output += "]";
	return output;
}

string getSimpleLinksJson(string dbname) {
	Database* db = Database::getDatabase(dbname);
	string output = "";
	for (unordered_map<Node*, Vertex*>::iterator it = db->graphMap->at(dbname)->vertexMap->begin(); it != db->graphMap->at(dbname)->vertexMap->end(); it++) {
		for (int i = 0; i < it->second->edgesVector.size(); i++)
		{
			Edge* e = it->second->edgesVector[i];
			if (output.empty()) {
				output = "[";
				output += "{ \"source\": " + to_string(e->originNode->id) + ", \"target\": " + to_string(e->targetNode->id) + "  , \"value\": " + e->properties["t"] + " }";
			}
			else
				output += ",{ \"source\": " + to_string(e->originNode->id) + ", \"target\": " + to_string(e->targetNode->id) + " , \"value\": " + e->properties["t"] + " }";
		}
		

	}
	if (!output.empty()) output += "]";
	return output;
}

void createDatasetHtml() {
	string nodejson = getSimpleNodesJson("test");
	string linkjson = getSimpleLinksJson("test");
	string dataset = "var dataset = { nodes: " + nodejson + " , edges: " + linkjson + "};";
	ofstream out("C:\\Users\\cmarisca\\Documents\\CRISTINA\\proy\\bridgeDB\\html_test\\dataset.js");
	out << dataset;
	out.close();
}

long main() {
	//generates_semi_random_graph("test2");
	/*
	string dbname = "test";
	load_graph_test(dbname);
	createDatasetHtml();
	Database* db = Database::getDatabase(dbname);
	Manipulation* m = new Manipulation(db->graphMap->at(dbname));
	/*m->deleteNode(4);
	createDatasetHtml();
	m->createEdge(3, 0, "", true);
	createDatasetHtml();
	Node* n = m->getNodeById(0);
	Node* nw = m->createNode(n->properties);
	createDatasetHtml();
	Edge* e1 = m->createEdge(nw, n, "", false);
	createDatasetHtml();
	Node* n = m->getNodeById(0);
	DijkstraWrapper* dg = db->graphMap->at(dbname)->vertexMap->at(n)->getDijkstraWrapper();
	DijkstraWrapper* r = m->UniformCostSearchById(dg, 2, "t", NULL, NULL);
	DijkstraWrapper* curr = r;
	cout << endl << "RESULT!!" << endl << endl;
	while (curr->previousVertex!=NULL) {
		cout << "current: " << curr->node->id << endl;
		curr = curr->previousVertex;
	}
	
	vector<Vertex*> pattern;
	pattern.push_back(db->graphMap->at(dbname)->vertexMap->at(n));
	vector<Vertex*>* resVec = m->getPathByPattern(pattern);
	//*/

	Database* db = Database::getDatabase("test2");
	cout << "CONFIG EDGE DIR: " << db->buildSotrePath("test2", ElementType::EDGE, false) << endl;
	Definition* d = new Definition(db);
	d->createGraph("testGraph");
	Graph* g = db->graphMap->at("testGraph");
	Manipulation* m = new Manipulation(g);
	Node* n1 = m->getNodeById(2);
	Node* n2 = m->createNode(n1->properties);
	m->createEdge(n1, n2, "", true);
	g->storeVertexMap();

	cout << "SALE" << endl;
	system("pause");
}
/*search node(s), edge(s)
-by id
-by property
-heuristic (by grouper)
*/
//generar arbol
//balancear arbol
//

//CREAR ERROR FRAMEWORK
//CREAR INPUT/OUTPUT/FORMATING FRAMEWORK
//SECURITY: USERS, GRANT PERMISSIONS, ENCRYPTION
//NETWORKING: CONECTIVITY
//COMMAND LINE
//WEB INTERFACE

/*
json / properties parser
file / path manager or storing
uuid generator
encryption for data management
configuration file that should contains :
-storage path
- database data files
- backup files
- installatio
- CREATE A LIST OF EDGES TO IMPROVE COMPLEXITY OF MANIPULATION OPS
- elements (node, edge and vertex) should be created with id=NULL (for comparision proupuses)
-arquitectura en comparisions
-comparar nodos dinamicamente map_contains_values?
*/

