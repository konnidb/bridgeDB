#pragma once
#include<iostream>
#include"Manipulation.h"
#include"..\utils\Comparison.h"

using namespace std;

//string serializeMap(unordered_map<string, string> properties);
//unordered_map<string, string> deserializeMap(string properties);


Node* Manipulation::createNode(unordered_map<string, string> properties) {
	Vertex* v = new Vertex();
	Node* n = new Node();
	n->properties = properties; //validate that doesn´t exists
	//ASSIGN ID TO NODE
	//ASSIGN ID TO VERTEX
	v->node = n;
	this->graph->vertexMap->insert({ n, v });
	return n;
}
Node* Manipulation::createNode(string properties) {
	unordered_map<string, string> props = deserializeMap(properties);
	return Manipulation::createNode(props);
}
Edge* Manipulation::createEdge(Node* originNode, Node* targetNode, unordered_map<string, string> properties, bool isDigraph) {
	if (originNode == NULL || targetNode == NULL)
		return NULL;
	Edge* e = new Edge(NULL, properties, originNode, targetNode); //assign ids
	for (unordered_map<Node*, Vertex*>::iterator it = this->graph->vertexMap->begin(); it != this->graph->vertexMap->end(); it++) 
	{
		if (it->first == originNode)
			this->graph->vertexMap->at(it->first)->edgesVector.push_back(e);
		//break? it shouldn´t contains more than one vertex with the same node
	}
	this->graph->vertexMap->at(originNode)->edgesVector.push_back(e);
	if(!isDigraph)
		this->graph->vertexMap->at(targetNode)->edgesVector.push_back(e);
	return e;
}

Edge* Manipulation::createEdge(Node * originNode, Node * targetNode, string properties, bool isDigraph) {
	unordered_map<string, string> props = deserializeMap(properties);
	return Manipulation::createEdge(originNode, targetNode, props, isDigraph);
}

Edge* Manipulation::createEdge(long originNodeId, long targetNodeId, unordered_map<string, string> properties, bool isDigraph) {
	Node* originNode = NULL;
	Node* targetNode = NULL;
	for (unordered_map<Node*, Vertex*>::iterator it = this->graph->vertexMap->begin(); it != this->graph->vertexMap->end(); it++)
	{
		if (it->first->id == originNodeId)
			originNode = it->first;
		if (it->first->id == targetNodeId)
			targetNode = it->first;
	}
	return Manipulation::createEdge(originNode, targetNode, properties, isDigraph);
}
Edge* Manipulation::createEdge(long originNodeId, long targetNodeId, string properties, bool isDigraph) {
	unordered_map<string, string> props = deserializeMap(properties);
	return Manipulation::createEdge(originNodeId, targetNodeId, props, isDigraph);
}
void Manipulation::deleteNode(long id) {
	Node* n = NULL;
	for (unordered_map<Node*, Vertex*>::iterator it = this->graph->vertexMap->begin(); it != this->graph->vertexMap->end(); it++)
	{
		if (it->first->id == id)
			n = it->first;
	}
	Manipulation::deleteNode(n);
}
void Manipulation::deleteNode(Node* node) {
	if (node == NULL)
		return;
	for (int i = 0; i < this->graph->vertexMap->at(node)->edgesVector.size(); i++)
	{
		this->graph->vertexMap->at(node)->edgesVector[i]->~Edge();
	}
	this->graph->vertexMap->at(node)->~Vertex();
	this->graph->vertexMap->erase(node);
	node->~Node();
}
void Manipulation::deleteNodes(unordered_map<string, string> toMatch) {
	if(toMatch.size() <= 0)
		return;
	for (unordered_map<Node*, Vertex*>::iterator it = this->graph->vertexMap->begin(); it != this->graph->vertexMap->end(); it++) {
		if (map_contains_values(it->first->properties, toMatch))
			Manipulation::deleteNode(it->first);
	}
}
void Manipulation::deleteEdge(long id) {
	Edge* e = NULL;
	for (unordered_map<Node*, Vertex*>::iterator it = this->graph->vertexMap->begin(); it != this->graph->vertexMap->end(); it++) {
		for (long i = 0; i < it->second->edgesVector.size(); i++)
		{
			if (it->second->edgesVector[i]->id == id) {
				e = it->second->edgesVector[i];
				break;
			}
		}
		if (e != NULL)
			break;
	}
	Manipulation::deleteEdge(e);
}
void Manipulation::deleteEdge(Edge* edge) {
	if (edge == NULL)
		return;
	for (unordered_map<Node*, Vertex*>::iterator it = this->graph->vertexMap->begin(); it != this->graph->vertexMap->end(); it++) {
		for (long i = 0; i < it->second->edgesVector.size(); i++)
		{
			if (it->second->edgesVector[i]==edge) {
				it->second->edgesVector.erase(it->second->edgesVector.begin()+i);
			}
		}
	}
	edge->~Edge();
}

void Manipulation::deleteEdges(unordered_map<string, string> toMatch) {
	if(toMatch.size() <= 0)
		return;
	for (unordered_map<Node*, Vertex*>::iterator it = this->graph->vertexMap->begin(); it != this->graph->vertexMap->end(); it++) {
		for (long i = 0; i < it->second->edgesVector.size(); i++)
		{
			if (map_contains_values(it->second->edgesVector[i]->properties, toMatch))
				Manipulation::deleteEdge(it->second->edgesVector[i]);
		}
	}
}
Node* Manipulation::getNodeById(long node) {
	for (unordered_map<Node*, Vertex*>::iterator it = this->graph->vertexMap->begin(); it != this->graph->vertexMap->end(); it++) {
		if (it->first->id == node)
			return it->first;
	}
	return NULL;
}

Node* Manipulation::getNodeByCondition(vector<Comparison> comp) {
	if (comp.size() <= 0)
		return NULL;
	for (unordered_map<Node*, Vertex*>::iterator it = this->graph->vertexMap->begin(); it != this->graph->vertexMap->end(); it++) {
		if (map_eval_values(it->first->properties, comp))
			return it->first;
	}
	return NULL;
}

Node* Manipulation::getNode(Node node) {
	if (node.properties.size() <= 0)
		return NULL;
	for (unordered_map<Node*, Vertex*>::iterator it = this->graph->vertexMap->begin(); it != this->graph->vertexMap->end(); it++) {
		if (map_contains_values(it->first->properties, node.properties))
			return it->first;
	}
	return NULL;
}

vector<Node*> Manipulation::getNodesByCondition(vector<Comparison> comp) {
	vector<Node*> NodeVector;
	if (comp.size() <= 0)
		return NodeVector;
	for (unordered_map<Node*, Vertex*>::iterator it = this->graph->vertexMap->begin(); it != this->graph->vertexMap->end(); it++) {
		if (map_eval_values(it->first->properties, comp))
			NodeVector.push_back(it->first);
	}
	return NodeVector;
}

vector<Node*> Manipulation::getNodes(Node node) {
	vector<Node*> NodeVector;
	if (node.properties.size() <= 0)
		return NodeVector;
	for (unordered_map<Node*, Vertex*>::iterator it = this->graph->vertexMap->begin(); it != this->graph->vertexMap->end(); it++) {
		if (map_contains_values(it->first->properties, node.properties))
			NodeVector.push_back(it->first);
	}
	return NodeVector;
}

Edge* Manipulation::getEdgeById(long edge) {
	if (edge == NULL)
		return NULL;
	for (unordered_map<Node*, Vertex*>::iterator it = this->graph->vertexMap->begin(); it != this->graph->vertexMap->end(); it++) {
		for (long i = 0; i < it->second->edgesVector.size(); i++)
		{
			if (it->second->edgesVector[i]->id == edge) {
				return it->second->edgesVector[i];
			}
		}
	}
	return NULL;
}

Edge* Manipulation::getEdgeByCondition(vector<Comparison> comp) {
	if (comp.size() <= 0)
		return NULL;
	for (unordered_map<Node*, Vertex*>::iterator it = this->graph->vertexMap->begin(); it != this->graph->vertexMap->end(); it++) {
		for (long i = 0; i < it->second->edgesVector.size(); i++)
		{
			if (map_eval_values(it->second->edgesVector[i]->properties, comp))
				return it->second->edgesVector[i];
		}
	}
	return NULL;
}

Edge* Manipulation::getEdge(Edge edge) {
	if (edge.properties.size() <= 0)
		return NULL;
	for (unordered_map<Node*, Vertex*>::iterator it = this->graph->vertexMap->begin(); it != this->graph->vertexMap->end(); it++) {
		for (long i = 0; i < it->second->edgesVector.size(); i++)
		{
			if (map_contains_values(it->second->edgesVector[i]->properties, edge.properties) && 
				edge.originNode != NULL ? edge.originNode->id == it->second->edgesVector[i]->originNode->id : true &&
				edge.targetNode != NULL ? edge.targetNode->id == it->second->edgesVector[i]->targetNode->id : true)
				return it->second->edgesVector[i];
		}
	}
	return NULL;
}

vector<Edge*> Manipulation::getEdgesByCondition(vector<Comparison> comp) {
	vector<Edge*> edgeVector;
	if (comp.size() <= 0)
		return edgeVector;
	for (unordered_map<Node*, Vertex*>::iterator it = this->graph->vertexMap->begin(); it != this->graph->vertexMap->end(); it++) {
		for (long i = 0; i < it->second->edgesVector.size(); i++)
		{
			if (map_eval_values(it->second->edgesVector[i]->properties, comp))
				edgeVector.push_back(it->second->edgesVector[i]);
		}
	}
	return edgeVector;
}

vector<Edge*> Manipulation::getEdges(Edge edge) {
	vector<Edge*> edgeVector;
	if (edge.properties.size() <= 0)
		return edgeVector;
	for (unordered_map<Node*, Vertex*>::iterator it = this->graph->vertexMap->begin(); it != this->graph->vertexMap->end(); it++) {
		for (long i = 0; i < it->second->edgesVector.size(); i++)
		{
			if (map_contains_values(it->second->edgesVector[i]->properties, edge.properties) &&
				edge.originNode != NULL ? edge.originNode->id == it->second->edgesVector[i]->originNode->id : true &&
				edge.targetNode != NULL ? edge.targetNode->id == it->second->edgesVector[i]->targetNode->id : true)
				edgeVector.push_back(it->second->edgesVector[i]);
		}
	}
	return edgeVector;
}

Vertex* Manipulation::getVertexById(long vertex) {
	for (unordered_map<Node*, Vertex*>::iterator it = this->graph->vertexMap->begin(); it != this->graph->vertexMap->end(); it++) {
		if (it->second->id == vertex)
			return it->second;
	}
	return NULL;
}

//Vertex* Manipulation::getVertexByCondition(vector<Comparison> comp) {}

Vertex* Manipulation::getVertex(Vertex vertex) {
	if (vertex.node == NULL && vertex.edgesVector.size() <= 0 && vertex.id == NULL)
		return NULL;
	for (unordered_map<Node*, Vertex*>::iterator it = this->graph->vertexMap->begin(); it != this->graph->vertexMap->end(); it++) {
		if (it->second->compare(&vertex))
			return it->second;
	}
	return NULL;
}

//vector<Vertex*> Manipulation::getVertexesByCondition(vector<Comparison> comp) {}

vector<Vertex*> Manipulation::getVertexes(Vertex vertex) {
	vector<Vertex*> vertexVector;
	if (vertex.node == NULL && vertex.edgesVector.size() <= 0 && vertex.id == NULL)
		return vertexVector;
	for (unordered_map<Node*, Vertex*>::iterator it = this->graph->vertexMap->begin(); it != this->graph->vertexMap->end(); it++) {
		if (it->second->compare(&vertex))
			vertexVector.push_back(it->second);
	}
	return vertexVector;
}


vector<Vertex*> Manipulation::getPathByProp(long rootNode, long tgtNode, string edgePropKey, bool isShortest) {
	vector<Vertex*> vertexVector;
	return vertexVector;
}

//vector<Vertex*> Manipulation::getPathByProp(Node* rootNode, Node* tgtNode, string propKey, bool isShortest) {}


Vertex* Manipulation::getPathByPattern(long rootNode, long tgtNode, Vertex pattern, bool isShortest) {
	return NULL;
}

DijkstraWrapper* Manipulation::UniformCostSearchById(DijkstraWrapper* root, int id, string edgePropKey, vector<DijkstraWrapper*>* toValidate, vector<DijkstraWrapper*>* validated)
{
	DijkstraWrapper* aux = NULL;
	if (toValidate == NULL)
		toValidate = new vector<DijkstraWrapper*>();
	if (validated == NULL)
	{
		validated = new vector<DijkstraWrapper*>();
		//ResetSearchLbls();
	}
	if (root != NULL)
	{
		if (root->node->id == id)
			return root;
		validated->push_back(root);

		for (int i = 0; i < root->edgesVector.size(); i++)
		{
			double value = (root->weight == NULL ? 0 : root->weight) + stod(root->edgesVector[i]->properties[edgePropKey]);
			DijkstraWrapper* tgtVertex = this->graph->vertexMap->at(root->node)->getDijkstraWrapper();
			if (tgtVertex->weight == NULL || tgtVertex->weight > value)
			{
				tgtVertex->previousVertex = root;
				tgtVertex->weight = value;
			}

			bool validatedContainsRoot = false;
			for (long i = 0; i < validated->size(); i++)
			{
				if (validated->at(i) == tgtVertex) {
					validatedContainsRoot = true;
					break;
				}
			}

			if (!validatedContainsRoot)
				toValidate->push_back(tgtVertex);
		}
		SortVertexListByWeight(toValidate, true);
	}
	if (toValidate->size() > 0)
	{
		DijkstraWrapper* tmp = toValidate->at(0);
		toValidate->erase(toValidate->begin());
		aux = this->UniformCostSearchById(tmp, id, edgePropKey, toValidate, validated);
	}
	return aux;
}

void Manipulation::SortVertexListByWeight(vector<DijkstraWrapper*>* toValidate, bool isShortest){}




