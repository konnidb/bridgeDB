#include<iostream>
#include<unordered_map>
#include<string>
#include"..\graph\structs\Node.h"

using namespace std;

class Main {
private:
	//Main instance;
public:
	static string databaseName;
	static unordered_map<string, string> configs;
	//static unordered_map<string, string> 

};


int main() {
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