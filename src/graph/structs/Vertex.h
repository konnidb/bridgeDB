#pragma once
#include<iostream>
#include"..\utils\Serializable.h"
#include"Edge.h"
#include"Node.h"
using namespace std;

class DijkstraWrapper;

class SerializableVertex : public Serializable {
public:
	vector<int> edgesIdVector;
	long node;
	SerializableVertex();
	//~SerializableVertex();
	void load(ifstream* streamObj);
	void store(ofstream* streamObj);
};

class Vertex : public Element {
public:
	long id;
	Node * node;
	vector<Edge *> edgesVector;
	Serializable* getSerializable(string path);
	Vertex();
	~Vertex();
	Vertex(long id, Node * node);
	bool compare(Vertex* vertex);
	DijkstraWrapper* getDijkstraWrapper();
private:
	DijkstraWrapper* selfDW;
};

class DijkstraWrapper : public Vertex {
public:
	DijkstraWrapper* previousVertex;
	double weight;
};
