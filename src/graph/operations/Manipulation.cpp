#pragma once
#include<iostream>
#include"Manipulation.h"
#include"..\utils\Comparison.h"

using namespace std;

//string serializeMap(unordered_map<string, string> properties);
//unordered_map<string, string> deserializeMap(string properties);

Manipulation::Manipulation(Graph* g) {
	this->graph = g;
}
Node* Manipulation::createNode(unordered_map<string, string> properties) {
	Vertex* v = new Vertex();
	Node* n = new Node();
	n->properties = properties; //validate that doesn´t exists
	n->id = this->graph->getNextNodeId();
	v->id = this->graph->getNextVertexId();
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
	long id = this->graph->getNextEdgeId();
	Edge* e = new Edge(id, properties, originNode, targetNode); 
	this->graph->vertexMap->at(originNode)->edgesVector.push_back(e);
	if (!isDigraph) {
		long id2 = this->graph->getNextEdgeId();
		Edge* e2 = new Edge(id2, properties, targetNode, originNode);
		this->graph->vertexMap->at(targetNode)->edgesVector.push_back(e2);
	}
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
	for (unordered_map<Node*, Vertex*>::iterator it = this->graph->vertexMap->begin(); it != this->graph->vertexMap->end(); it++) {
		for (int i = 0; i < it->second->edgesVector.size(); i++)
		{
			if (it->second->edgesVector[i]->targetNode == node) {
				this->deleteEdge(it->second->edgesVector[i]);
			}
				
		}
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
	if (vertex.node == NULL && vertex.edgesVector.size() <= 0)
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
	if (vertex.node == NULL && vertex.edgesVector.size() <= 0)
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


vector<Vertex*>* Manipulation::getPathByPattern(vector<Vertex*> pattern) {
	vector<Vertex*>* result = new vector<Vertex*>();
	for (long i = 0; i < pattern.size(); i++){
		if (pattern[i]->isEmpty())
			return NULL;
		Vertex* matchingVertex = NULL;
		for (unordered_map<Node*, Vertex*>::iterator it = this->graph->vertexMap->begin(); it != this->graph->vertexMap->end(); it++) {
			if (!pattern[i]->node->isEmpty() && Node::compareNodes(it->first, pattern[i]->node))
				matchingVertex = it->second;
			else
				continue;
			for (long j = 0; j < pattern[i]->edgesVector.size(); j++){
				if (!pattern[i]->edgesVector[j]->isEmpty()) {
					bool matchesEdge = false;
					for (long k = 0; k < it->second->edgesVector.size(); k++) {
						if (Edge::compareEdges(it->second->edgesVector[k], pattern[i]->edgesVector[j])) {
							matchesEdge = true;
							break;
						}
					}
					if (!matchesEdge) {
						matchingVertex = NULL;
						break;
					}
				}
			}
		}
		if (matchingVertex == NULL)
			return NULL;
		result->push_back(matchingVertex);
	}
	if (result->size() > 0)
		return result;
	return NULL;
}

DijkstraWrapper* Manipulation::UniformCostSearchById(DijkstraWrapper* root, int id, string edgePropKey, vector<DijkstraWrapper*>* toValidate, vector<DijkstraWrapper*>* validated)
{
	cout << endl << "ENTRA BUSQUEDA DIJSTRA!! root: " << root->node->id << endl;
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
			double edgeW = stod(root->edgesVector[i]->properties[edgePropKey]);
			double value = (root->weight == NULL ? 0 : root->weight) + edgeW;
			DijkstraWrapper* tgtVertex = this->graph->vertexMap->at(root->edgesVector[i]->targetNode)->getDijkstraWrapper();
			bool validatedtgtVertex = false;
			for (long i = 0; i < validated->size(); i++)
			{
				if (validated->at(i)->node->id == tgtVertex->node->id) {
					validatedtgtVertex = true;
					break;
				}
			}
			if (validatedtgtVertex) continue;
			if (tgtVertex->weight == NULL || tgtVertex->weight > value)
			{
				/*if (tgtVertex->weight != NULL)
					cout << endl << "TGT: " << tgtVertex->node->id << endl
					<< "tgt parent: " << (tgtVertex->previousVertex != NULL? tgtVertex->previousVertex->node->id:NULL) << endl
					<< "tgt prev weight: " << tgtVertex->weight << endl
					<< "new value: " << value << endl
					<< "root: " << root->node->id << endl
					<< "root prev: " << ((root->previousVertex != NULL )? root->previousVertex->node->id : NULL)<< endl;*/
				tgtVertex->previousVertex = root;
				tgtVertex->weight = value;
			}

			bool toValidatetgtVertex = false;
			for (long i = 0; i < toValidate->size(); i++)
			{
				if (toValidate->at(i)->node->id == tgtVertex->node->id) {
					toValidatetgtVertex = true;
					break;
				}
			}

			if (!toValidatetgtVertex)
				toValidate->push_back(tgtVertex);
		}
		QuickSort(toValidate, 0, toValidate->size()-1, 1);
	}
	if (toValidate->size() > 0)
	{
		DijkstraWrapper* tmp = toValidate->at(0);
		toValidate->erase(toValidate->begin());
		aux = this->UniformCostSearchById(tmp, id, edgePropKey, toValidate, validated);
	}
	return aux;
}

//void Manipulation::SortVertexListByWeight(vector<DijkstraWrapper*>* toValidate, bool isShortest){}

void Manipulation::QuickSort(vector<DijkstraWrapper*>* toValidate, int min, int max, const short isShortest) //1=asc -1=desc
{
	int p = (max + min) / 2;
	double pivot;
	if (toValidate->at(p)->weight == NULL)
		pivot = 0;
	else
		pivot = toValidate->at(p)->weight * isShortest;
	int i = min - 1;
	int j = max + 1;
	do
	{
		double pivotMin = NULL;
		double pivotMax = NULL;
		do
		{
			i++;
			if (toValidate->at(i)->weight == NULL)
				pivotMin = 0;
			else
				pivotMin = toValidate->at(i)->weight * isShortest;
		} while (pivot > pivotMin);
		do
		{
			j--;
			if (toValidate->at(j)->weight == NULL)
				pivotMax = 0;
			else
				pivotMax = toValidate->at(j)->weight * isShortest;
		} while (pivot < pivotMax);

		if (i <= j)
		{
			DijkstraWrapper* aux = toValidate->at(i);
			toValidate->at(i) = toValidate->at(j);
			toValidate->at(j) = aux;
			i++;
			j--;
		}

	} while (i <= j);
	if (min < j)
		QuickSort(toValidate, min, j, isShortest);
	if (max > i)
		QuickSort(toValidate, i, max, isShortest);
}




