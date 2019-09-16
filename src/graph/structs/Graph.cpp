#pragma once
#include<iostream>
#include<string>
#include<filesystem>
#include"Vertex.h"
#include"Schema.h"
#include"Graph.h"
#include"..\..\storage\IndexHandler.cpp"
#include"..\..\admin\ConfigFile.cpp"
//#include"..\..\utils\Enums.h"
using namespace std;

ConfigFileHandler* getConfigFileHandler(string databaseName);
bool fileExists(string path);

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
	unordered_map<string, ofstream*> pageFiles;
	vector<Node*> nodesVector;
	vector<Edge*> edgesVector;
	for (int i = 0; i < this->vertexVector.size(); i++) {
		string pageId;
		if (index.indexMap.find(to_string(vertexVector[i]->id)) == index.indexMap.end())
			pageId = index.indexMap[to_string(vertexVector[i]->id)];
		else
			pageId = to_string(index.getNextPageId());
		index.indexMap[to_string(vertexVector[i]->id)] = pageId;
		string pagePath = vertexDir + pageId + pageExtension;
		if (pageFiles.find(pagePath) == pageFiles.end()) {
			pageFiles[pagePath] = new ofstream(pagePath, ios::out | ios::binary);
		}
		SerializableVertex v = this->vertexVector[i]->getSerializable(pagePath);
		v.store(pageFiles[pagePath]);
		if (find(nodesVector.begin(), nodesVector.end(), this->vertexVector[i]->node) == nodesVector.end())
			nodesVector.push_back(this->vertexVector[i]->node);
		for (int j = 0; j < this->vertexVector[i]->edgesVector.size(); j++)
		{
			if (find(edgesVector.begin(), edgesVector.end(), this->vertexVector[i]->edgesVector[j]) == edgesVector.end())
				edgesVector.push_back(this->vertexVector[i]->edgesVector[j]);
		}
	}
}

void Graph::storeEdgeVector(vector<Edge*> edgesVector) {
}

void Graph::storeNodeVector(vector<Node*> nodesVector) {
}

void Graph::storeSchemaVector() {

}

void Graph::loadVertexVector() {

}

void Graph::loadSchemaVector() {

}