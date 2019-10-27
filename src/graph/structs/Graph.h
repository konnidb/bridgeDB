#pragma once
#include<iostream>
#include<string>
#include <vector>
#include <unordered_map>
#include"Vertex.h"
#include"Schema.h"
#include "Node.h"
using namespace std;

class Graph {
public:
	long id;
	string databaseName;
	string name;
	//vector<Schema*> schemaVector;
	unordered_map<Node*, Vertex*>* vertexMap;

	Graph(string databaseName);

	void storeVertexMap();

	void storeEdgeVector(vector<Edge*> edgesVector);

	void storeNodeVector(vector<Node*> nodesVector);

	void storeSchemaVector();

	void loadVertexMap(vector<Node*> nodeVector, vector<Edge*> edgeVector);

	vector<Edge*> loadEdgeVector(vector<Node*> nodeVector);

	vector<Node*> loadNodeVector();

	long getNextVertexId();
	long getNextNodeId();
	long getNextEdgeId();

	//void loadSchemaVector();


};