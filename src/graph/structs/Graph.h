#pragma once
#include<iostream>
#include<string>
#include"Vertex.h"
#include"Schema.h"
using namespace std;

class Graph {
public:
	int id;
	string databaseName;
	string name;
	vector<Schema*> schemaVector;
	vector<Vertex*> vertexVector;

	Graph(string databaseName);

	void storeVertexVector();

	void storeEdgeVector(vector<Edge*> edgesVector);

	void storeNodeVector(vector<Node*> nodesVector);

	void storeSchemaVector();

	void loadVertexVector(vector<Node*> nodeVector, vector<Edge*> edgeVector);

	vector<Edge*> loadEdgeVector(vector<Node*> nodeVector);

	vector<Node*> loadNodeVector();

	void loadSchemaVector();


};