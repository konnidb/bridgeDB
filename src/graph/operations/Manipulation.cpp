//#pragma once
//#include<iostream>
//#include"../structs/Graph.cpp"
//
//using namespace std;
//
//string serializeMap(unordered_map<string, string> properties);
//unordered_map<string, string> deserializeMap(string properties);
//
//class Comparison {
//	ComparisonOperator comparisonOperator;
//	LogicOperator logicOperator;
//	string key;
//	string value;
//	DataType dataType;
//};
//
//
//class Manipulation {
//public:
//	static Graph* graph;
//	static Node* createNode(unordered_map<string, string> properties) {
//		Vertex* v = new Vertex();
//		Node* n = new Node();
//		n->properties = properties; //validate that doesn´t exists
//		//ASSIGN ID TO NODE
//		//ASSIGN ID TO VERTEX
//		v->node = n;
//		Manipulation::graph->vertexVector.push_back(v);
//		return n;
//	}
//	static Node* createNode(string properties) {
//		unordered_map<string, string> props = deserializeMap(properties);
//		return Manipulation::createNode(props);
//	}
//	static Edge* createEdge(Node* originNode, Node* targetNode, unordered_map<string, string> properties) {
//		if (originNode == NULL || targetNode == NULL)
//			return NULL;
//		Edge* e = new Edge(NULL, properties, originNode, targetNode); //assign ids
//		for (long i = 0; i < Manipulation::graph->vertexVector.size(); i++)
//		{
//			if (Manipulation::graph->vertexVector[i]->node == originNode)
//				Manipulation::graph->vertexVector[i]->edgesVector.push_back(e);
//			//break? it shouldn´t contains more than one vertex with the same node
//		}
//		return e;
//	}
//	static Edge* createEdge(Node* originNode, Node* targetNode, string properties) {
//		unordered_map<string, string> props = deserializeMap(properties);
//		return Manipulation::createEdge(originNode, targetNode, props);
//	}
//	static Edge* createEdge(long originNodeId, long targetNodeId, unordered_map<string, string> properties) {
//		Node* originNode = NULL;
//		Node* targetNode = NULL;
//		for (long i = 0; i < Manipulation::graph->vertexVector.size(); i++)
//		{
//			if (Manipulation::graph->vertexVector[i]->node->id == originNodeId)
//				originNode = Manipulation::graph->vertexVector[i]->node;
//			if (Manipulation::graph->vertexVector[i]->node->id == targetNodeId)
//				targetNode = Manipulation::graph->vertexVector[i]->node;
//		}
//		return Manipulation::createEdge(originNode, targetNode, properties);
//	}
//	static Edge* createEdge(long originNodeId, long targetNodeId, string properties) {
//		Node* originNode = NULL;
//		Node* targetNode = NULL;
//		for (long i = 0; i < Manipulation::graph->vertexVector.size(); i++)
//		{
//			if (Manipulation::graph->vertexVector[i]->node->id == originNodeId)
//				originNode = Manipulation::graph->vertexVector[i]->node;
//			if (Manipulation::graph->vertexVector[i]->node->id == targetNodeId)
//				targetNode = Manipulation::graph->vertexVector[i]->node;
//		}
//		unordered_map<string, string> props = deserializeMap(properties);
//		return Manipulation::createEdge(originNode, targetNode, props);
//	}
//	/*
//	static void deleteNode(long id) {}
//	static void deleteNode(Node node) {}
//	static void deleteNodes(unordered_map<string, string> properties) {}
//	static void deleteEdge(Edge edge) {}
//	static void deleteEdges(unordered_map<string, string> properties) {}
//	*/
//	static void createRelation(Node nodeSrc, Node nodeTgt) {}
//	static void createRelation(long nodeSrc, long nodeTgt) {}
//	static void createRelation(Node nodeSrc, Node nodeTgt, unordered_map<string, string> edgeProperties) {}
//	static void createRelation(long nodeSrcId, long nodeTgtId, unordered_map<string, string> edgeProperties) {}
//	static Node searchNodeById(long node) {}
//	static Node searchNodeByCondition(vector<Comparison> comp) {}
//	static vector<Node> searchNodesByCondition(vector<Comparison> comp) {}
//	static void searchNode(Node node) {}
//	
//};


//create nultiple relations?
//get path search (dijstra?)
//asignación de ids // uudis
//create and assign schema
//store node and edge list on graph?

//sustituir vertexVector por un mapa con llave node