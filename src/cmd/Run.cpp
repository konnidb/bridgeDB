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

using namespace std;

string gen_random(const int len) {
	string s;
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";
	s.resize(len);
	for (int i = 0; i < len; ++i) {
		s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
	}
	return s;
}

void generates_semi_random_graph() {
	int id = 1;
	string dbname = "test";
	Database db = Database::getDatabase(dbname);
	/*db.cfg->configFileMap[ConfigFileAttrbute::databaseName] = dbname;
	db.cfg->configFileMap[ConfigFileAttrbute::pageExtension] = ".bdb";
	db.cfg->configFileMap[ConfigFileAttrbute::edgeDirectory] = "C:\\Users\\L440\\Documents\\BRIDGEDB\\bridgeDB\\dataTests\\edge\\";
	db.cfg->configFileMap[ConfigFileAttrbute::edgeIndexFile] = "edge.ix";
	db.cfg->configFileMap[ConfigFileAttrbute::nodeDirectory] = "C:\\Users\\L440\\Documents\\BRIDGEDB\\bridgeDB\\dataTests\\node\\";
	db.cfg->configFileMap[ConfigFileAttrbute::nodeIndexFile] = "node.ix";
	db.cfg->configFileMap[ConfigFileAttrbute::vertexDirectory] = "C:\\Users\\L440\\Documents\\BRIDGEDB\\bridgeDB\\dataTests\\vertex\\";
	db.cfg->configFileMap[ConfigFileAttrbute::vertexIndexFile] = "vertex.ix";
	db.cfg->configFileMap[ConfigFileAttrbute::schemaDirectory] = "C:\\Users\\L440\\Documents\\BRIDGEDB\\bridgeDB\\dataTests\\schema\\";
	db.cfg->configFileMap[ConfigFileAttrbute::schemaIndexFile] = "schema.ix";
	db.cfg->storeConfigFile();*/
	db.cfg->loadConfigFile();
	cout << "CONFIG EDGE DIR: " << db.cfg->configFileMap[ConfigFileAttrbute::edgeDirectory] << endl;
	//*
	Graph g(db.name);
	db.graphVector.push_back(&g);
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
	g.schemaVector.push_back(s1);

	for (int i = 0; i < 138; i++)
	{
		Node* n = new Node();
		n->id = id++;
		for (unordered_map<string, string>::iterator it = properties.begin(); it != properties.end(); it++)
		{
			if (it->second==to_string(DataType::NUM))
				n->properties[it->first] = to_string((rand() % 1000000000) + 1000000000);
			else
				n->properties[it->first] = gen_random(10);
		}
		n->schema = s1;
		Vertex* v = new Vertex();
		v->id = id++;
		v->node = n;
		g.vertexVector.push_back(v);
	}

	int size = (int)g.vertexVector.size();
	for (int i = 0; i < size; i++)
	{
		for (int j = 1; j <= 3 && i + j<size; j++)
		{
			Edge* e = new Edge();
			e->id = id++;
			e->originNode = g.vertexVector[i]->node;
			e->targetNode = g.vertexVector[i + j]->node;
			g.vertexVector[i]->edgesVector.push_back(e);
		}
	}

	cout << "holi" << endl;

	g.storeVertexVector();
	//*/
}

void load_graph_test() {
	string dbname = "test";
	Database db = Database::getDatabase(dbname);
	if(db.cfg->configFileMap.size()==0)
		db.cfg->loadConfigFile();
	cout << "CONFIG EDGE DIR: " << db.cfg->configFileMap[ConfigFileAttrbute::edgeDirectory] << endl;
	Graph* g = new Graph(db.name);
	db.graphVector.push_back(g);
	vector<Node*> nv = g->loadNodeVector();
	vector<Edge*> ev = g->loadEdgeVector(nv);
	g->loadVertexVector(nv, ev);
}


int main() {
	string t = "test.txt";

	char a = 'd';
	string s = "holi";
	cout << s + a + s << endl;

	///*
	Node n1;
	n1.id = 222;
	n1.properties["testeefwfwf"] = "holis";
	n1.properties["edgarqdqwdqwd"] = "vazquez";
	n1.properties["cristina"] = "mariscalsdcsdcs";

	SerializableNode*  ser = dynamic_cast<SerializableNode*>(n1.getSerializable(t));
	cout << "SER ID: " << ser->id << endl;
	//ser->store(NULL);

	//*
	SerializableNode  ser2;
	ser2.path = t;
	ser2.load(NULL);
	cout << ser2.id << endl;
	for (unordered_map<string, string>::iterator it = ser2.properties.begin(); it != ser2.properties.end(); it++) {
		cout << "IT " << it->first.length() << endl;
		cout << "val " << it->second.length() << endl;
		for (int i = 0; i < it->first.length(); i++)
		{
			cout << it->first[i];
		}
		cout << endl;
	}

	//*/
	//*
	string p = "C:\\Users\\L440\\Documents\\BRIDGEDB\\bridgeDB\\dataTests\\node\\1.bdb";
	ifstream* rf = new ifstream(p, ios::in | ios::binary);
	cout << "SIZE OUT INT: " << sizeof(long long) << endl;
	cout << "SIZE OUT bool: " << sizeof(bool) << endl;
	cout << "SIZE OUT char *: " << sizeof(char *) << endl;
	int j = 999999999999999;
	char * ab = (char*)&j;
	cout << "SIZE OUT int to char *: " << sizeof(ab) << endl;
	for (int i = 0; i < sizeof(ab); i++)
	{
		cout << (int)ab[i]<<endl;
	}
	j = (int)*ab;
	cout << "GET BACK FROM CAST: " << j<< endl;
	rf->read(ab, sizeof(ab));
	cout <<endl<< "AFTER READ! " << endl;
	for (int i = 0; i < sizeof(ab); i++)
	{
		cout <<(int) ab[i]<<endl;
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
	//generates_semi_random_graph();
	//load_graph_test();
	cout << "SALE" << endl;
	system("pause");
}

/*
int main(string args[]) {
for (int i = 0; i < sizeof(args)/sizeof(string); i++)
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
*/


//how to use it?
/*
for (const auto&[key, val] : s1.properties)
{
std::cout << key         // string (key)
<< ':'
<< val        // string's value
<< std::endl;
}
*/
