#pragma once
#include<iostream>
#include<string>
#include"Vertex.h"
#include"Schema.h"
using namespace std;

class Graph {
public:
	int id; 
	string name;
	vector<Schema*> schemaVector;
	vector<Vertex*> vertexVector;
	Graph(){}
};