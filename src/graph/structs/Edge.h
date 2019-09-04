#pragma once
#include<iostream>
#include"Node.h"
#include"..\utils\Serializable.h"

using namespace std;

class EdgeSerializable : Serializable {
public:
	int originNode;
	int targetNode;
	EdgeSerializable();
};

class Edge {
public:
	Node originNode;
	Node targetNode;
	EdgeSerializable getSerializable();
};