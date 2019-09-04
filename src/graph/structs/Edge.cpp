//#pragma once
#include<iostream>
#include"Edge.h"
using namespace std;

EdgeSerializable::EdgeSerializable() {
	this->objType = EDGE;
}

EdgeSerializable Edge::getSerializable() {
	return EdgeSerializable();
}

