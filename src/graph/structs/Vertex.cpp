#pragma once
#include<iostream>
#include"Vertex.h"
using namespace std;

VertexSerializable::VertexSerializable() {
	this->objType = VERTEX;
}

VertexSerializable Vertex::getSerializable() {
	VertexSerializable serializable;
	serializable.id = this->id;
	for (int i = 0; i < (int)this->edgesVector.size(); i++)
	{
		serializable.edgesIdVector.push_back(this->edgesVector[i]->id);
	}
	return serializable;
}
