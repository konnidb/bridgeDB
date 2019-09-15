#include<iostream>
#include<unordered_map>
//#include"..\utils\dependencies\json.hpp"
#include<string>
#include"..\graph\structs\Node.h"
#include"..\graph\structs\Edge.h"
//#include"..\graph\structs\Vertex.h"
#include"..\graph\structs\Database.cpp"
#include"..\utils\Enums.h"

using namespace std;



string gen_random(const int len) {
	string s;
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	for (int i = 0; i < len; ++i) {
		s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
	}
	return s;
}


class Main {
private:
	//Main instance;
public:
	static Database database;
	static unordered_map<string, string> configs;

};

Database Main::database;
unordered_map<string, string> Main::configs;

void generates_semi_random_graph(){
	int id = 1;
	Main::database.name = "test";
	Graph g;
	Main::database.graphVector.push_back(&g);
	g.name = "testGraph";
	g.id = id++;
	Schema s1;
	s1.id = id++;
	s1.name = "persona";
	s1.type = ElementType::NODE;
	unordered_map<string, string> properties;
	properties["nombre"] = to_string(DataType::STR);
	properties["edad"] = to_string(DataType::NUM);
	properties["telefono"] = to_string(DataType::STR);
	properties["correo"] = to_string(DataType::STR);
	properties["pw"] = to_string(DataType::STR);
	s1.properties = properties;
	g.schemaVector.push_back(&s1);

	for (int i = 0; i < 100; i++)
	{
		Node n;
		n.id = id++;
		for (unordered_map<string, string>::iterator it = properties.begin(); it != properties.end(); it++)
		{
			if (it->second._Equal(to_string(DataType::NUM)))
				n.properties[it->first] = (rand() % 1000000000) + 1000000000;
			else
				n.properties[it->first] = gen_random(10);
		}
		Vertex v;
		v.id = id++;
		v.node = &n;
		g.vertexVector.push_back(&v);
	}

	int size = (int)g.vertexVector.size();
	for (int i = 0; i < size; i++)
	{
		for (int j = 1; j <= 3 && i + j<size; j++)
		{
			Edge e;
			e.id = id++;
			e.originNode = g.vertexVector[i]->node;
			e.targetNode = g.vertexVector[i + j]->node;
			g.vertexVector[i]->edgesVector.push_back(&e);
		}
	}
}

void config_main() {
	Main::configs["NodesPath"] = "nodes_test.txt";
	Main::configs["EdgesPath"] = "edges_test.txt";
	Main::configs["VertexPath"] = "vertex_test.txt";
	Main::configs["GraphPath"] = "graph_test.txt";
}

void store_graph() {
	config_main();
	Graph * g = Main::database.graphVector[0];
	int size = (int)g->vertexVector.size();
	for (int  i = 0; i < size; i++)
	{

	}
}

void load_graph() {
	config_main();
}

int main() {
	string t = "test.txt";

	char a = 'd';
	string s = "holi";
	cout << s+a+s << endl;

	///*
	Node n1;
	n1.id = 222;
	n1.properties["testeefwfwf"] = "holis";
	n1.properties["edgarqdqwdqwd"] = "vazquez";
	n1.properties["cristina"] = "mariscalsdcsdcs";
	
	SerializableNode  ser = n1.getSerializable();
	cout << "SER ID: " << ser.id << endl;
	ser.path = t;
	//ser.store();
	
	//*
	SerializableNode  ser2;
	ser2.path = t;
	ser2.load();
	cout << ser2.id<<endl;
	for (unordered_map<string, string>::iterator it = ser2.properties.begin(); it != ser2.properties.end(); it++) {
		cout << "IT " << it->first.length() << endl;
		cout << "val " << it->second.length() << endl;
		for (size_t i = 0; i < it->first.length(); i++)
		{
			cout << it->first[i];
		}
		cout << endl;
	}
	
	//*/
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
