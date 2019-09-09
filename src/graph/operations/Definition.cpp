#pragma once
#include<iostream>
#include"../structs/Edge.h"
#include"../structs/Node.h"
#include"../structs/Graph.cpp"
#include"../structs/Database.cpp"
#include"../structs/Schema.cpp"


enum LogicOperator {
	AND,
	OR,
	NAND,
	NOR,
	N
};

enum ComparisonOperator {
	EQ, //equals
	DF, //different
	GT, //great than
	GE, //great or equals than
	LT, //less than
	LE, //less or equals than
	RX //regex
};

enum DataType {
	NUM,
	STR,
	BOOL,
	CAT,
	DT
};

class Comparison {
	ComparisonOperator comparisonOperator;
	LogicOperator logicOperator;
	string key;
	string value;
	DataType dataType;
};


class Definition {
public:
	Database database;
	Definition(Database database){}
	Definition(string database) {}
	static void createDatabase(string name){}
	Graph createGraph(){}
	Schema createSchema(){}
	void deleteDatabase(){}
	void deleteSchema() {}
	void deleteGraph() {}
	void loadGraph(){}
};

class Manipulation {
public:
	Graph graph;
	Manipulation(Graph graph) {}
	Manipulation(string graphName) {}
	static Node createNode(unordered_map<string, string> properties) {}
	static Node createNode(string properties) {}
	static Edge createEdge(unordered_map<string, string> properties) {}
	static Edge createEdge(string properties) {}
	static void deleteNode(int id) {}
	static void deleteNode(Node node) {}
	static void deleteNodes(unordered_map<string, string> properties) {}
	static void deleteEdge(Edge edge) {}
	static void deleteEdges(unordered_map<string, string> properties) {}
	static void createRelation(Node nodeSrc, Node nodeTgt) {}
	static void createRelation(int nodeSrc, int nodeTgt) {}
	static void createRelation(Node nodeSrc, Node nodeTgt, unordered_map<string, string> edgeProperties) {}
	static void createRelation(int nodeSrcId, int nodeTgtId, unordered_map<string, string> edgeProperties) {}
	static Node searchNodeById(int node) {}
	static Node searchNodeByCondition(list<Comparison> comp) {}
	static list<Node> searchNodesByCondition(list<Comparison> comp) {}
	static void searchNode(Node node) {}
	//create nultiple relations?
};