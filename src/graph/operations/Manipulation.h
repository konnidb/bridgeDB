#pragma once
#include<iostream>
#include"../structs/Graph.h"
#include"../utils/Comparison.h"

using namespace std;

string serializeMap(unordered_map<string, string> properties);
unordered_map<string, string> deserializeMap(string properties);
bool map_contains_values(unordered_map<string, string> properties, unordered_map<string, string> toMatch);
bool map_eval_values(unordered_map<string, string> properties, vector<Comparison> toMatch);

class Manipulation {
public:
	Graph* graph;
	Node* createNode(unordered_map<string, string> properties);
	Node* createNode(string properties);
	Edge* createEdge(Node* originNode, Node* targetNode, unordered_map<string, string> properties, bool isDigraph);
	Edge* createEdge(Node* originNode, Node* targetNode, string properties, bool isDigraph);
	Edge* createEdge(long originNodeId, long targetNodeId, unordered_map<string, string> properties, bool isDigraph);
	Edge* createEdge(long originNodeId, long targetNodeId, string properties, bool isDigraph);
	void deleteNode(long id);
	void deleteNode(Node* node);
	void deleteNodes(unordered_map<string, string> toMatch);
	void deleteEdge(long id);
	void deleteEdge(Edge* edge);
	void deleteEdges(unordered_map<string, string> toMatch);
	Node* getNodeById(long node);
	Node* getNodeByCondition(vector<Comparison> comp);
	Node* getNode(Node node);
	vector<Node*> getNodesByCondition(vector<Comparison> comp);
	vector<Node*> getNodes(Node node);
	Edge* getEdgeById(long edge);
	Edge* getEdgeByCondition(vector<Comparison> comp);
	Edge* getEdge(Edge edge);
	vector<Edge*> getEdgesByCondition(vector<Comparison> comp);
	vector<Edge*> getEdges(Edge edge);
	Vertex* getVertexById(long vertex);
	//Vertex* getVertexByCondition(vector<Comparison> comp);
	Vertex* getVertex(Vertex vertex);
	//vector<Vertex*> getVertexesByCondition(vector<Comparison> comp);
	vector<Vertex*> getVertexes(Vertex vertex);

	vector<Vertex*> getPathByProp(long rootNode, long tgtNode, string edgePropKey, bool isShortest);
	//vector<Vertex*> getPathByProp(Node* rootNode, Node* tgtNode, string propKey, bool isShortest);

	Vertex* getPathByPattern(long rootNode, long tgtNode, Vertex pattern, bool isShortest);
	DijkstraWrapper* UniformCostSearchById(DijkstraWrapper* root, int id, string edgePropKey, vector<DijkstraWrapper*>* toValidate, vector<DijkstraWrapper*>* validated);
	void SortVertexListByWeight(vector<DijkstraWrapper*>* toValidate, bool isShortest);

};