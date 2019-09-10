#include<iostream>
#include<unordered_map>
#include<string>
#include"..\graph\structs\Node.h"
#include"..\graph\structs\Database.cpp"
#include"..\utils\Enums.h"

using namespace std;

class Main {
private:
	//Main instance;
public:
	static Database database;
	static unordered_map<string, string> configs;

};

Database Main::database;

int main() {
	int id = 1;
	Main::database.name = "test";
	Graph g;
	g.name = "testGraph";
	g.id = id++;
	Main::database.graphVector.push_back(g);
	Schema s1;
	s1.id = id++;
	s1.name = "persona";
	s1.type = ElementType::NODE;
	s1.properties["nombre"] = to_string(DataType::STR);
	s1.properties["edad"] = to_string(DataType::NUM);
	s1.properties["telefono"] = to_string(DataType::STR);
	s1.properties["correo"] = to_string(DataType::STR);
	s1.properties["pw"] = to_string(DataType::STR);
	g.schemaVector.push_back(&s1);

	int tmp = 0;
	for (int i = 0; i < 100; i++)
	{
		Node n;
		n.id = id++;
		for (unordered_map<string, string>::iterator it = s1.properties.begin(); it != s1.properties.end(); it++)
		{
			if (it->second._Equal(to_string(DataType::NUM)))
				n.properties[it->first] = to_string(tmp++);
			else
				n.properties[it->first] = "kfmkemfklsef";
		}
		Vertex v;
		v.node = &n;
		g.vertexVector.push_back(&v);
	}

	for (int i = 0; i < g.vertexVector.size-3; i++)
	{
		g.vertexVector[i]->edgesVector;
	}
	

	/*
	for (const auto&[key, val] : s1.properties)
	{
		std::cout << key         // string (key)
			<< ':'
			<< val        // string's value
			<< std::endl;
	}
	*/

	Node n1;
	n1.id = 1;
	n1.properties["test"] = "holis";
	n1.properties["edgar"] = "vazquez";
	n1.properties["cristina"] = "mariscal";
	string t = "test.txt";
	SerializableNode  ser = n1.getSerializable();
	ser.path = t;
	ser.store();
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