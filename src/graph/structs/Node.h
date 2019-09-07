#pragma once
#include<iostream>
#include"..\utils\Serializable.h"
#include"Edge.h"
using namespace std;

class NodeSerializable : Serializable {
public:
	list<int> edgesIdList;
	NodeSerializable();
};

class Node {
public:
	unordered_map<string, string> properties;
	list<Edge> edgesList;
	NodeSerializable getSerializable();
};