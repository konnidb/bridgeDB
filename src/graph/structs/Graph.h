#pragma once
#include<iostream>
#include<string>
#include <vector>
#include <unordered_map>
#include"Vertex.h"
#include"Schema.h"
#include "Node.h"
#include "Edge.h"
using namespace std;

class Graph {
public:
	long id;
	string databaseName;
	string name;
	unordered_map<Node*, Vertex*>* vertexMap;
	unordered_map<long, Schema*>* schemaMap;

	static Graph* getGraph(string databaseName, string graphName);

	void storeVertexMap();

	void storeEdgeVector(vector<Edge*> edgesVector);

	void storeNodeVector(vector<Node*> nodesVector);

	void storeSchemaMap();

	void loadVertexMap(vector<Node*> nodeVector, vector<Edge*> edgeVector);

	vector<Edge*> loadEdgeVector(vector<Node*> nodeVector);

	vector<Node*> loadNodeVector();

	long getNextVertexId();
	long getNextNodeId();
	long getNextEdgeId();

	void loadSchemaMap();

	vector<Edge*> getEdgeVector();
	vector<Node*> getNodeVector();
private:
	Graph(string databaseName, string graphName);
};