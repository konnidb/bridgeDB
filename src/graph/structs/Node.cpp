//#pragma once
#include<iostream>
#include"Node.h"
//#include"..\utils\Serializable.h"
using namespace std;

SerializableNode::SerializableNode() {
	this->objType = NODE;
}

SerializableNode Node::getSerializable() {
	SerializableNode serializable;
	serializable.id = this->id;
	serializable.properties = this->properties;
	return serializable;
}

Node::Node() {

}