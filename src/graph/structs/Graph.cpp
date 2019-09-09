#pragma once
#include<iostream>
#include<string>
#include"Node.h"
#include"Schema.cpp"
using namespace std;

class Graph {
public:
	int id; 
	string name;
	list<Schema*> schemas;
	list<Node*> nodeList;
};