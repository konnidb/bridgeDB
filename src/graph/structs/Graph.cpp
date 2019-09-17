#pragma once
#include<iostream>
#include<string>
#include<filesystem>
#include"Vertex.h"
#include"Schema.h"
#include"Graph.h"
#include"..\..\storage\IndexHandler.cpp"
#include"..\..\admin\ConfigFile.cpp"
//#include<dynamic>
//#include"..\..\utils\Enums.h"
using namespace std;

template <class T >
T* vectorFindByFn(vector<T*> vectorEvl, T* elmnt, bool(*compareFn)(T* elmnt1, T* elmnt2)) {
	for (int i = 0; i < vectorEvl.size(); i++)
	{
		if (compareFn(elmnt, vectorEvl[i]))
			return vectorEvl[i];
	}
	return NULL;
}

template<class T>
T* vectorFindById(vector<T*> vectorEvl, T* elmnt) {
	for (int i = 0; i < vectorEvl.size(); i++)
	{
		if (elmnt->id == vectorEvl[i]->id)
			return vectorEvl[i];
	}
	return NULL;
}
ConfigFileHandler* getConfigFileHandler(string databaseName);
bool fileExists(string path);
bool compareEdges(Edge* edge1, Edge* edge2);

void closeStreamsOnMap(unordered_map<string, ofstream*> pageFiles) {
	for (unordered_map<string, ofstream*>::iterator it = pageFiles.begin(); it != pageFiles.end(); it++) {
		if (it->second->is_open()) it->second->close();
		if (!it->second->good()) cout << "closeStreamsOnMap: FAILED CLOSING "<< it->first << endl; //ErrorMap::error_loading_object->action();
	}
}

Graph::Graph(string databaseName) {
	this->databaseName = databaseName;
}

void Graph::storeVertexVector() {
	ConfigFileHandler* cfg = getConfigFileHandler(this->databaseName);
	string vertexDir = cfg->configFileMap[ConfigFileAttrbute::vertexDirectory];
	string pageExtension = cfg->configFileMap[ConfigFileAttrbute::pageExtension];
	string vertexIndexPath = vertexDir + cfg->configFileMap[ConfigFileAttrbute::vertexIndexFile];
	IndexHandler index(vertexIndexPath);
	if (fileExists(vertexIndexPath))
		index.loadIndex();
	//IF NOT EXISTS, CREATE NEW
	unordered_map<string, ofstream*> pageFiles;
	vector<Node*> nodesVector;
	vector<Edge*> edgesVector;
	for (int i = 0; i < this->vertexVector.size(); i++) {
		string pageId;
		if (index.indexMap.find(to_string(this->vertexVector[i]->id)) == index.indexMap.end())
			pageId = index.indexMap[to_string(this->vertexVector[i]->id)];
		else
			pageId = to_string(index.getNextPageId());
		index.indexMap[to_string(this->vertexVector[i]->id)] = pageId;
		string pagePath = vertexDir + pageId + pageExtension;
		if (pageFiles.find(pagePath) == pageFiles.end()) {
			pageFiles[pagePath] = new ofstream(pagePath, ios::out | ios::app | ios::binary);
		}
		SerializableVertex* s = dynamic_cast<SerializableVertex*>( this->vertexVector[i]->getSerializable(pagePath));
		s->store(pageFiles[pagePath]);
		if (find(nodesVector.begin(), nodesVector.end(), this->vertexVector[i]->node) == nodesVector.end())
			nodesVector.push_back(this->vertexVector[i]->node);
		for (int j = 0; j < this->vertexVector[i]->edgesVector.size(); j++)
		{
			if (find(edgesVector.begin(), edgesVector.end(), this->vertexVector[i]->edgesVector[j]) == edgesVector.end())
				edgesVector.push_back(this->vertexVector[i]->edgesVector[j]);
		}
	}
	this->storeEdgeVector(edgesVector);
	this->storeNodeVector(nodesVector);
	closeStreamsOnMap(pageFiles);
}

void Graph::storeEdgeVector(vector<Edge*> edgesVector) {
	ConfigFileHandler* cfg = getConfigFileHandler(this->databaseName);
	string edgeDir = cfg->configFileMap[ConfigFileAttrbute::edgeDirectory];
	string pageExtension = cfg->configFileMap[ConfigFileAttrbute::pageExtension];
	string edgeIndexPath = edgeDir + cfg->configFileMap[ConfigFileAttrbute::edgeIndexFile];
	IndexHandler index(edgeIndexPath);
	if (fileExists(edgeIndexPath))
		index.loadIndex();
	//IF NOT EXISTS, CREATE NEW
	unordered_map<string, ofstream*> pageFiles;
	for (int i = 0; i < edgesVector.size(); i++) {
		string pageId;
		if (index.indexMap.find(to_string(edgesVector[i]->id)) == index.indexMap.end())
			pageId = index.indexMap[to_string(edgesVector[i]->id)];
		else
			pageId = to_string(index.getNextPageId());
		index.indexMap[to_string(edgesVector[i]->id)] = pageId;
		string pagePath = edgeDir + pageId + pageExtension;
		if (pageFiles.find(pagePath) == pageFiles.end()) {
			pageFiles[pagePath] = new ofstream(pagePath, ios::out | ios::app | ios::binary);
		}
		SerializableEdge* s = dynamic_cast<SerializableEdge*>(edgesVector[i]->getSerializable(pagePath));
		s->store(pageFiles[pagePath]);
	}
	closeStreamsOnMap(pageFiles);
}

void Graph::storeNodeVector(vector<Node*> nodesVector) {
	ConfigFileHandler* cfg = getConfigFileHandler(this->databaseName);
	string nodeDir = cfg->configFileMap[ConfigFileAttrbute::nodeDirectory];
	string pageExtension = cfg->configFileMap[ConfigFileAttrbute::pageExtension];
	string nodeIndexPath = nodeDir + cfg->configFileMap[ConfigFileAttrbute::nodeIndexFile];
	IndexHandler index(nodeIndexPath);
	if (fileExists(nodeIndexPath))
		index.loadIndex();
	//IF NOT EXISTS, CREATE NEW
	unordered_map<string, ofstream*> pageFiles;
	for (int i = 0; i < nodesVector.size(); i++) {
		string pageId;
		if (index.indexMap.find(to_string(nodesVector[i]->id)) == index.indexMap.end())
			pageId = index.indexMap[to_string(nodesVector[i]->id)];
		else
			pageId = to_string(index.getNextPageId());
		index.indexMap[to_string(nodesVector[i]->id)] = pageId;
		string pagePath = nodeDir + pageId + pageExtension;
		if (pageFiles.find(pagePath) == pageFiles.end()) {
			pageFiles[pagePath] = new ofstream(pagePath, ios::out | ios::app | ios::binary);
		}
		SerializableNode* s = dynamic_cast<SerializableNode*>(nodesVector[i]->getSerializable(pagePath));
		s->store(pageFiles[pagePath]);
	}
	closeStreamsOnMap(pageFiles);
}

void Graph::storeSchemaVector() {
	ConfigFileHandler* cfg = getConfigFileHandler(this->databaseName);
	string schemaDir = cfg->configFileMap[ConfigFileAttrbute::schemaDirectory];
	string pageExtension = cfg->configFileMap[ConfigFileAttrbute::pageExtension];
	string schemaIndexPath = schemaDir + cfg->configFileMap[ConfigFileAttrbute::schemaIndexFile];
	IndexHandler index(schemaIndexPath);
	if (fileExists(schemaIndexPath))
		index.loadIndex();
	//IF NOT EXISTS, CREATE NEW
	unordered_map<string, ofstream*> pageFiles;
	for (int i = 0; i < this->schemaVector.size(); i++) {
		string pageId;
		if (index.indexMap.find(to_string(this->schemaVector[i]->id)) == index.indexMap.end())
			pageId = index.indexMap[to_string(this->schemaVector[i]->id)];
		else
			pageId = to_string(index.getNextPageId());
		index.indexMap[to_string(this->schemaVector[i]->id)] = pageId;
		string pagePath = schemaDir + pageId + pageExtension;
		if (pageFiles.find(pagePath) == pageFiles.end()) {
			pageFiles[pagePath] = new ofstream(pagePath, ios::out | ios::app | ios::binary);
		}
		this->schemaVector[i]->store(pageFiles[pagePath]);
	}
	closeStreamsOnMap(pageFiles);
}

void Graph::loadVertexVector(vector<Node*> nodeVector, vector<Edge*> edgeVector) {
	ConfigFileHandler* cfg = getConfigFileHandler(this->databaseName);
	string vertexDir = cfg->configFileMap[ConfigFileAttrbute::vertexDirectory];
	string pageExtension = cfg->configFileMap[ConfigFileAttrbute::pageExtension];
	string vertexIndexPath = vertexDir + cfg->configFileMap[ConfigFileAttrbute::vertexIndexFile];
	IndexHandler index(vertexIndexPath);
	if (fileExists(vertexIndexPath))
		index.loadIndex();
	//IF NOT EXISTS, CREATE NEW
	vector<string> pageIds;
	for (unordered_map<string, string>::iterator it = index.indexMap.begin(); it != index.indexMap.end(); it++) {
		if (find(pageIds.begin(), pageIds.end(), it->second) == pageIds.end())
			pageIds.push_back(it->second);
	}
	for (int i = 0; i < pageIds.size(); i++)
	{
		ifstream* rf = new ifstream(pageIds[i], ios::in | ios::binary);
		while (rf) {
			SerializableVertex s;
			s.load(rf);
			//Vertex v
		}
		
	}
	/*
	unordered_map<string, ofstream*> pageFiles;
	vector<Node*> nodesVector;
	vector<Edge*> edgesVector;
	for (int i = 0; i < this->vertexVector.size(); i++) {
		string pageId;
		if (index.indexMap.find(to_string(this->vertexVector[i]->id)) == index.indexMap.end())
			pageId = index.indexMap[to_string(this->vertexVector[i]->id)];
		else
			pageId = to_string(index.getNextPageId());
		index.indexMap[to_string(this->vertexVector[i]->id)] = pageId;
		string pagePath = vertexDir + pageId + pageExtension;
		if (pageFiles.find(pagePath) == pageFiles.end()) {
			pageFiles[pagePath] = new ofstream(pagePath, ios::out | ios::app | ios::binary);
		}
		SerializableVertex s = this->vertexVector[i]->getSerializable(pagePath);
		s.store(pageFiles[pagePath]);
		if (find(nodesVector.begin(), nodesVector.end(), this->vertexVector[i]->node) == nodesVector.end())
			nodesVector.push_back(this->vertexVector[i]->node);
		for (int j = 0; j < this->vertexVector[i]->edgesVector.size(); j++)
		{
			if (find(edgesVector.begin(), edgesVector.end(), this->vertexVector[i]->edgesVector[j]) == edgesVector.end())
				edgesVector.push_back(this->vertexVector[i]->edgesVector[j]);
		}
	}
	this->storeEdgeVector(edgesVector);
	this->storeNodeVector(nodesVector);
	closeStreamsOnMap(pageFiles);
	*/
}

vector<Edge*> Graph::loadEdgeVector(vector<Node*> nodeVector) {
	vector<Edge*> edgeVector;
	ConfigFileHandler* cfg = getConfigFileHandler(this->databaseName);
	string edgeDir = cfg->configFileMap[ConfigFileAttrbute::edgeDirectory];
	string pageExtension = cfg->configFileMap[ConfigFileAttrbute::pageExtension];
	string edgeIndexPath = edgeDir + cfg->configFileMap[ConfigFileAttrbute::edgeIndexFile];
	IndexHandler index(edgeIndexPath);
	if (fileExists(edgeIndexPath))
		index.loadIndex();
	//IF NOT EXISTS, CREATE NEW
	vector<string> pageIds;
	for (unordered_map<string, string>::iterator it = index.indexMap.begin(); it != index.indexMap.end(); it++) {
		if (find(pageIds.begin(), pageIds.end(), it->second) == pageIds.end())
			pageIds.push_back(it->second);
	}
	for (int i = 0; i < pageIds.size(); i++)
	{
		ifstream* rf = new ifstream(pageIds[i], ios::in | ios::binary);
		while (rf) {
			SerializableEdge serializable;
			serializable.load(rf);
			Edge* edge = new Edge(serializable);
			//Edge* result = vectorFindById<Edge>(edgeVector, edge);
			Edge* result = vectorFindByFn<Edge>(edgeVector, edge, Edge::compareEdges);
			//bool(*test)(Edge* e, Edge* e2) = Edge::compareEdges;
			if (result == NULL)
				edgeVector.push_back(edge);
			else
				edge = result;
			if (edge->originNode == NULL) {
				//Node* originNode = vectorFindById<Node>(nodeVector, new Node(serializable.originNode));
				Node* originNode = vectorFindByFn<Node>(nodeVector, new Node(serializable.originNode), Node::compareNodes);
				if (originNode == NULL)
					cout << "ERROR! NODO ORIGEN NO ENCONTRADO!" << endl;
				else
					edge->originNode = originNode;
			}

			if (edge->targetNode == NULL) {
				//Node* targetNode = vectorFindById<Node>(nodeVector, new Node(serializable.targetNode));
				Node* targetNode = vectorFindByFn<Node>(nodeVector, new Node(serializable.targetNode), Node::compareNodes);
				if (targetNode == NULL)
					cout << "ERROR! NODO ORIGEN NO ENCONTRADO!" << endl;
				else
					edge->targetNode = targetNode;
			}
		}
		rf->close();
		if (rf->fail()) cout << "loadEdgeVector: fail closing ifstream on file: " << pageIds[i] << endl;
	}
	return edgeVector;
}

vector<Node*> Graph::loadNodeVector() {
	vector<Node*> nodeVector;
	ConfigFileHandler* cfg = getConfigFileHandler(this->databaseName);
	string nodeDir = cfg->configFileMap[ConfigFileAttrbute::nodeDirectory];
	string pageExtension = cfg->configFileMap[ConfigFileAttrbute::pageExtension];
	string nodeIndexPath = nodeDir + cfg->configFileMap[ConfigFileAttrbute::nodeIndexFile];
	IndexHandler index(nodeIndexPath);
	if (fileExists(nodeIndexPath))
		index.loadIndex();
	//IF NOT EXISTS, CREATE NEW
	vector<string> pageIds;
	for (unordered_map<string, string>::iterator it = index.indexMap.begin(); it != index.indexMap.end(); it++) {
		if (find(pageIds.begin(), pageIds.end(), it->second) == pageIds.end())
			pageIds.push_back(it->second);
	}
	for (int i = 0; i < pageIds.size(); i++)
	{
		ifstream* rf = new ifstream(pageIds[i], ios::in | ios::binary);
		while (rf) {
			SerializableNode serializable;
			serializable.load(rf);
			Node* node = new Node(serializable);
			//Node* result = vectorFindById<Node>(nodeVector, node);
			Node* result = vectorFindByFn<Node>(nodeVector, node, *Node::compareNodes);
			if (result == NULL)
				nodeVector.push_back(node);
		}
		rf->close();
		if (rf->fail()) cout << "loadNodeVector: fail closing ifstream on file: " << pageIds[i] << endl;
	}
	return nodeVector;
}

void Graph::loadSchemaVector() {

}