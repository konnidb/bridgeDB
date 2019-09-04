#pragma once
#include<iostream>
#include"..\utils\Serializable.h"
//#include"Edge.h"
using namespace std;

class NodeSerializable : Serializable {
public:
	list<int> edgesIdList;
	NodeSerializable();
};

class Node {
public:
//	list<Edge> edgesList;
	NodeSerializable getSerializable();
};