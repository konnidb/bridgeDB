//#pragma once
#include<iostream>
#include"Node.h"
using namespace std;

NodeSerializable::NodeSerializable() {
	this->objType = NODE;
}

NodeSerializable Node::getSerializable() {
	return NodeSerializable();
}
