#pragma once
#include<iostream>
//#include"Edge.h"
#include"Node.h"
#include<Schema>
using namespace std;

class Graph {
public:
	string name;
	list<Schema> schemas;
	list<Node*> nodeList;
	int id;
	string name;
};