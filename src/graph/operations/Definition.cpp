#pragma once
#include<iostream>
#include"../structs/Edge.h"
#include"../structs/Node.h"
#include"../structs/Graph.cpp"
#include"../structs/Schema.cpp"

class Definition {
public:
	
	static int createDatabase(){}
	static Graph createGraph(){}
	static Schema createSchema(){}
	static int deleteDatabase(){}
	static int deleteSchema() {}
	static int deleteGraph() {}
	static int loadGraph(){}
};

class Manipulation {
public:
	static Node createNode(unordered_map<string, string> properties) {}
	static Node createNode(string properties) {}
	static Edge createEdge(unordered_map<string, string> properties) {}
	static Edge createEdge(string properties) {}
	static void deleteNode(int id){}
	static void deleteNode(Node node) {}
	static void deleteNodes(unordered_map<string, string> properties) {}
	static void deleteEdge(Edge edge) {}
	static void deleteEdges(unordered_map<string, string> properties) {}
	static void createRelation(Node nodeSrc, Node nodeTgt){}
	static void createRelation(Node nodeSrc, Node nodeTgt, unordered_map<string, string> edgeProperties) {}
	static void createRelation(int nodeSrcId, int nodeTgtId, unordered_map<string, string> edgeProperties) {}
	//create nultiple relations?




	//delete node and edge
	//modfy node and edge
	//create realtion
	/*search node(s), edge(s)
		-by id
		-by property
		-heuristic (by grouper)
	*/
};

//generar arbol
//balancear arbol
//

//CREAR ERROR FRAMEWORK
//CREAR IMPUT/OUTPUT/FORMATING FRAMEWORK
//SECURITY: USERS, GRANT PERMISSIONS, ENCRYPTION
//NETWORKING: CONECTIVITY
//COMMAND LINE
//WEB INTERFACE