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
	Database db = Database::getDatabase(dbname);
	/*
	db.cfg->configFileMap[ConfigFileAttrbute::databaseName] = dbname;
	db.cfg->configFileMap[ConfigFileAttrbute::pageExtension] = ".bdb";
	db.cfg->configFileMap[ConfigFileAttrbute::edgeDirectory] = "C:\\Users\\cmarisca\\Documents\\CRISTINA\\proy\\dataTests\\edge\\";
	db.cfg->configFileMap[ConfigFileAttrbute::edgeIndexFile] = "edge.ix";
	db.cfg->configFileMap[ConfigFileAttrbute::nodeDirectory] = "C:\\Users\\cmarisca\\Documents\\CRISTINA\\proy\\dataTests\\node\\";
	db.cfg->configFileMap[ConfigFileAttrbute::nodeIndexFile] = "node.ix";
	db.cfg->configFileMap[ConfigFileAttrbute::vertexDirectory] = "C:\\Users\\cmarisca\\Documents\\CRISTINA\\proy\\dataTests\\vertex\\";
	db.cfg->configFileMap[ConfigFileAttrbute::vertexIndexFile] = "vertex.ix";
	db.cfg->configFileMap[ConfigFileAttrbute::schemaDirectory] = "C:\\Users\\cmarisca\\Documents\\CRISTINA\\proy\\dataTests\\schema\\";
	db.cfg->configFileMap[ConfigFileAttrbute::schemaIndexFile] = "schema.ix";
	db.cfg->storeConfigFile();
	//*/
	db.cfg->loadConfigFile();
	cout << "CONFIG EDGE DIR: " << db.cfg->configFileMap[ConfigFileAttrbute::edgeDirectory] << endl;
	Graph g(db.name);
	db.graphVector->push_back(&g);
	g.name = "testGraph";
	g.id = id++;
	Schema* s1 = new Schema();
	s1->id = id++;
	s1->name = "persona";
	s1->type = ElementType::NODE;
	unordered_map<string, string> properties;
	properties["nombre"] = to_string(DataType::STR);
	properties["edad"] = to_string(DataType::NUM);
	properties["telefono"] = to_string(DataType::STR);
	properties["correo"] = to_string(DataType::STR);
	properties["pw"] = to_string(DataType::STR);
	s1->properties = properties;
	//g.schemaVector.push_back(s1);
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
			if (it->second == to_string(DataType::NUM))
				n->properties[it->first] = to_string((rand() % 1000000000) + 1000000000);
			else
				n->properties[it->first] = gen_random(10);
		}
		n->schema = s1;
		Vertex* v = new Vertex();
		v->id = vertexId++;
		v->node = n;
		nodeVec.push_back(n);
		g.vertexMap->insert({ n, v });
	}
	int count = 0;
	for (unordered_map<Node*, Vertex*>::iterator it = g.vertexMap->begin(); it != g.vertexMap->end(); it++) {
		{
			for (long j = count; j < count+3 && j < nodeVec.size(); j++)
			{
				Edge* e = new Edge();
				e->id = edgeId++;
				e->originNode = it->first;
				e->targetNode = nodeVec[j];
				it->second->edgesVector.push_back(e);
			}
			count++;
		}
	}
		cout << "holi" << endl;
		g.storeVertexMap();
}

void load_graph_test(string dbname) {
	Database db = Database::getDatabase(dbname);
	if(db.cfg->configFileMap.size()==0)
		db.cfg->loadConfigFile();
	cout << "CONFIG EDGE DIR: " << db.cfg->configFileMap[ConfigFileAttrbute::edgeDirectory] << endl;
	Graph* g = new Graph(db.name);
	db.graphVector->push_back(g);
	vector<Node*> nv = g->loadNodeVector();
	vector<Edge*> ev = g->loadEdgeVector(nv);
	g->loadVertexMap(nv, ev);
}

string getSimpleNodesJson(string dbname){
	Database db = Database::getDatabase(dbname);
	string output= "";
	for (unordered_map<Node*, Vertex*>::iterator it = db.graphVector->at(0)->vertexMap->begin(); it != db.graphVector->at(0)->vertexMap->end(); it++) {
		if (output.empty()) {
			output = "[";
			output += "{ \"name\": \"" + it->first->properties["nombre"] + "\" }";// , \"group\":  " + it->first->properties["group"] + " }";
		}else
			output += ",{ \"name\": \"" + it->first->properties["nombre"] + "\" }";// , \"group\": " + it->first->properties["group"] + " }";
	}
	if(!output.empty()) output += "]";
	return output;
}

string getSimpleLinksJson(string dbname) {
	Database db = Database::getDatabase(dbname);
	string output = "";
	for (unordered_map<Node*, Vertex*>::iterator it = db.graphVector->at(0)->vertexMap->begin(); it != db.graphVector->at(0)->vertexMap->end(); it++) {
		for (int i = 0; i < it->second->edgesVector.size(); i++)
		{
			Edge* e = it->second->edgesVector[i];
			if (output.empty()) {
				output = "[";
				output += "{ \"source\": " + to_string(e->originNode->id) + ", \"target\": " + to_string(e->targetNode->id) + " }"; // , \"value\": " + e->properties["value"] + " }";
			}
			else
				output += ",{ \"source\": " + to_string(e->originNode->id) + ", \"target\": " + to_string(e->targetNode->id) + " }"; // , \"value\": " + e->properties["value"] + " }";
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
	/*string t = "test.txt";

	char a = 'd';
	string s = "holi";
	cout << s + a + s << endl;
	unordered_map<string, string> mapT;

	mapT["h"] = "holis";
	mapT["j"] = "holis";
	mapT["k"] = "holis";
	mapT["l"] = "holis";



	
	Node n1;
	n1.id = 2222;
	n1.properties["testeefwfwf"] = "holis";
	n1.properties["edgarqdqwdqwd"] = "vazquez";
	n1.properties["cristina"] = "mariscalsdcsdcs";

	SerializableNode*  ser = dynamic_cast<SerializableNode*>(n1.getSerializable(t));
	cout << "SER ID: " << ser->id << endl;
	ser->store(NULL);

	//*
	SerializableNode  ser2;
	ser2.path = t;
	ser2.load(NULL);
	cout << ser2.id << endl;
	for (unordered_map<string, string>::iterator it = ser2.properties.begin(); it != ser2.properties.end(); it++) {
		cout << "IT " << it->first.length() << endl;
		cout << "val " << it->second.length() << endl;
		for (long i = 0; i < it->first.length(); i++)
		{
			cout << it->first[i];
		}
		cout << endl;
	}

	//*/
	/*
	string p = "C:\\Users\\L440\\Documents\\BRIDGEDB\\bridgeDB\\dataTests\\node\\1.bdb";
	ifstream* rf = new ifstream(p, ios::in | ios::binary);
	cout << "SIZE OUT INT: " << sizeof(long long) << endl;
	cout << "SIZE OUT bool: " << sizeof(bool) << endl;
	cout << "SIZE OUT char *: " << sizeof(char *) << endl;
	long j = 999999999999999;
	char * ab = (char*)&j;
	cout << "SIZE OUT long to char *: " << sizeof(ab) << endl;
	for (long i = 0; i < sizeof(ab); i++)
	{
		cout << (long)ab[i]<<endl;
	}
	j = (long)*ab;
	cout << "GET BACK FROM CAST: " << j<< endl;
	rf->read(ab, sizeof(ab));
	cout <<endl<< "AFTER READ! " << endl;
	for (long i = 0; i < sizeof(ab); i++)
	{
		cout <<(long) ab[i]<<endl;
	}
	j = (long long)*ab;
	cout << "NEW J: " << j << endl;
	char o = '1';
	while(o=='1') {
		bool size;
		rf->read((char *)&size, sizeof(size));
		cout << size << endl;
		cin >> o;
	}
	rf->close();
	//*/
	//generates_semi_random_graph("test");
	load_graph_test("test");
	//createDatasetHtml();
	Database db = Database::getDatabase("test");
	Manipulation* m = new Manipulation(db.graphVector->at(0));
	m->deleteNode(15);
	createDatasetHtml();
	cout << "SALE" << endl;
	system("pause");
}

/*
long main(string args[]) {
for (long i = 0; i < sizeof(args)/sizeof(string); i++)
{
//if(.compare(args[i]))
}
}
//*/



//CREATE STRUC FOR OPERATIONS (suma, resta, mult, div, promedio, con, pass fn as attr, concat, convert (to str, to num, to datetime), get datetime format...)
//HANDLE DATETIME
//id validator famework: props just can have alphanum chars

/*search node(s), edge(s)
-by id
-by property
-heuristic (by grouper)
*/




//generar arbol
//balancear arbol
//

//CREAR ERROR FRAMEWORK
//CREAR IMPUT/OUTPUT/FORMATING FRAMEWORK
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

