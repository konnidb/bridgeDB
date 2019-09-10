#pragma once
#include<iostream>
#include<string>
#include"Vertex.cpp"
#include"Schema.cpp"
using namespace std;

class Graph {
public:
	int id; 
	string name;
	vector<Schema*> schemaVector;
	vector<Vertex*> vertexVector;
};