#pragma once
#include<iostream>
#include"Edge.h"
using namespace std;

SerializableEdge::SerializableEdge() {
	this->objType = EDGE;
}

SerializableEdge Edge::getSerializable() {
	return SerializableEdge();
}

