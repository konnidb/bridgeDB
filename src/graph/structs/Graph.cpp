#pragma once
#include<iostream>
//#include"Edge.h"
#include"Node.h"
using namespace std;

class Graph {
public:
	list<Node*> nodeList;
	int id;
	string name;
};