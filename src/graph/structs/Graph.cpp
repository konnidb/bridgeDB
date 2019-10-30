#pragma once
#include<iostream>
#include<string>
#include<filesystem>
#include"Vertex.h"
#include"Schema.h"
#include"Graph.h"
#include"..\..\storage\IndexHandler.cpp"
#include"..\..\admin\ConfigFile.h"
#include"Database.h"
using namespace std;

long char_ptr_to_int(char* c);

template <class T >
T* vectorFindByFn(vector<T*> vectorEvl, T* elmnt, bool(*compareFn)(T* elmnt1, T* elmnt2)) {
	for (long i = 0; i < vectorEvl.size(); i++)
	{
		if (compareFn(elmnt, vectorEvl[i]))
			return vectorEvl[i];
	}
	return NULL;
}

template<class T>
T* vectorFindById(vector<T*> vectorEvl, T* elmnt) {
	for (long i = 0; i < vectorEvl.size(); i++)
	{
		if (elmnt->id == vectorEvl[i]->id)
			return vectorEvl[i];
	}
	return NULL;
}
ConfigFileHandler* getConfigFileHandler(string databaseName);
bool fileExists(string path);

void closeStreamsOnMap(unordered_map<string, ofstream*> pageFiles) {
	for (unordered_map<string, ofstream*>::iterator it = pageFiles.begin(); it != pageFiles.end(); it++) {
		if (it->second->is_open()) it->second->close();
		if (!it->second->good()) cout << "closeStreamsOnMap: FAILED CLOSING "<< it->first << endl; //ErrorMap::error_loading_object->action();
	}
}

Graph* Graph::getGraph(string databaseName, string graphName) {
	Database* db = Database::getDatabase(databaseName);
	vector<string> graphNames = db->getGraphNames();
	if (db->graphMap->find(graphName) != db->graphMap->end())
		return db->graphMap->at(graphName);
	else
		return new Graph(databaseName, graphName);
}

Graph::Graph(string databaseName, string graphName) {
	this->databaseName = databaseName;
	this->name = graphName;
	vertexMap = new unordered_map<Node*, Vertex*>();
	schemaMap = new unordered_map<long, Schema*>();
	Database* db = Database::getDatabase(databaseName);
	vector<string> graphNames = db->getGraphNames();
	if (db->graphMap->find(graphName) == db->graphMap->end() && find(graphNames.begin(), graphNames.end(), graphName) != graphNames.end()) {
		this->loadSchemaMap();
		vector<Node*> nv = this->loadNodeVector();
		vector<Edge*> ev = this->loadEdgeVector(nv);
		this->loadVertexMap(nv, ev);
	}
	(*db->graphMap)[graphName] = this;
}

void Graph::storeVertexMap() {
	ConfigFileHandler* cfg = getConfigFileHandler(this->databaseName);
	string vertexDir = Database::getDatabase(this->databaseName)->buildSotrePath(this->name, ElementType::VERTEX, true);
	string pageExtension = (*cfg->configFileMap)[ConfigFileAttrbute::pageExtension];
	string vertexIndexPath = vertexDir + (*cfg->configFileMap)[ConfigFileAttrbute::vertexIndexFile];
	IndexHandler index(vertexIndexPath);
	string pageId = "";
	string pagePath = "";
	unordered_map<string, ofstream*> pageFiles;
	//if (fileExists(vertexIndexPath))
		//index.loadIndex();
	//else {
		pageId = to_string(index.getNextPageId());
		pagePath = vertexDir + pageId + pageExtension;
		if (pageFiles.find(pagePath) == pageFiles.end()) {
			pageFiles[pagePath] = new ofstream(pagePath, ios::out | ios::binary); //new ofstream(pagePath, ios::out | ios::app | ios::binary);
			long size = this->vertexMap->size();
			char* sizec = (char*)& size;
			unsigned char* c = (unsigned char*)sizec;
			pageFiles[pagePath]->write((char*)& size, sizeof(long));
		}
	//}
	//IF NOT EXISTS, CREATE NEW
	vector<Node*> nodesVector;
	vector<Edge*> edgesVector;
	for (unordered_map<Node*, Vertex*>::iterator it = this->vertexMap->begin(); it != this->vertexMap->end(); it++) {
		//if(index.indexMap.find(to_string(it->second->id))==index.indexMap.end())
		index.indexMap[to_string(it->second->id)] = pageId;
		SerializableVertex* s = dynamic_cast<SerializableVertex*>(it->second->getSerializable(pagePath));
		s->store(pageFiles[pagePath]); 
		if (find(nodesVector.begin(), nodesVector.end(), it->first) == nodesVector.end())
			nodesVector.push_back(it->first);
		for (long j = 0; j < it->second->edgesVector.size(); j++)
		{
			if (find(edgesVector.begin(), edgesVector.end(), it->second->edgesVector[j]) == edgesVector.end())
				edgesVector.push_back(it->second->edgesVector[j]);
		}
	}
	index.storeIndex();
	this->storeEdgeVector(edgesVector);
	this->storeNodeVector(nodesVector);
	closeStreamsOnMap(pageFiles);
}

void Graph::storeEdgeVector(vector<Edge*> edgesVector) {
	ConfigFileHandler* cfg = getConfigFileHandler(this->databaseName);
	string edgeDir = Database::getDatabase(this->databaseName)->buildSotrePath(this->name, ElementType::EDGE, true);
	string pageExtension = (*cfg->configFileMap)[ConfigFileAttrbute::pageExtension];
	string edgeIndexPath = edgeDir + (*cfg->configFileMap)[ConfigFileAttrbute::edgeIndexFile];
	bool newPage = false;
	IndexHandler index(edgeIndexPath);
	string pageId = "";
	string pagePath = "";
	unordered_map<string, ofstream*> pageFiles;
	//if (fileExists(edgeIndexPath))
		//index.loadIndex();
	//else {
		pageId = to_string(index.getNextPageId());
		pagePath = edgeDir + pageId + pageExtension;
		if (pageFiles.find(pagePath) == pageFiles.end()) {
			pageFiles[pagePath] = new ofstream(pagePath, ios::out | ios::binary); //new ofstream(pagePath, ios::out | ios::app | ios::binary);
			long size = edgesVector.size();
			char* sizec = (char*)& size;
			unsigned char* c = (unsigned char*)sizec;
			pageFiles[pagePath]->write((char*)& size, sizeof(long));
		}
	//}
	for (long i = 0; i < edgesVector.size(); i++) {
		index.indexMap[to_string(edgesVector[i]->id)] = pageId;
		SerializableEdge* s = dynamic_cast<SerializableEdge*>(edgesVector[i]->getSerializable(pagePath));
		s->store(pageFiles[pagePath]);
	}
	index.storeIndex();
	closeStreamsOnMap(pageFiles);
}

void Graph::storeNodeVector(vector<Node*> nodesVector) {
	ConfigFileHandler* cfg = getConfigFileHandler(this->databaseName);
	string nodeDir = Database::getDatabase(this->databaseName)->buildSotrePath(this->name, ElementType::NODE, true);
	string pageExtension = (*cfg->configFileMap)[ConfigFileAttrbute::pageExtension];
	string nodeIndexPath = nodeDir + (*cfg->configFileMap)[ConfigFileAttrbute::nodeIndexFile];
	IndexHandler index(nodeIndexPath);
	string pageId = "";
	unordered_map<string, ofstream*> pageFiles;
	string pagePath;
	//if (fileExists(nodeIndexPath))
		//index.loadIndex();
	//else{
		pageId = to_string(index.getNextPageId());
		pagePath = nodeDir + pageId + pageExtension;
		if (pageFiles.find(pagePath) == pageFiles.end()) {
			pageFiles[pagePath] = new ofstream(pagePath, ios::out | ios::binary); //new ofstream(pagePath, ios::out | ios::app | ios::binary);
			long size = nodesVector.size();
			char* sizec = (char*)&size;
			unsigned char* c = (unsigned char*)sizec;
			pageFiles[pagePath]->write((char *)&size, sizeof(long));
		}
	//}
	for (long i = 0; i < nodesVector.size(); i++) {
		index.indexMap[to_string(nodesVector[i]->id)] = pageId;
		SerializableNode* s = dynamic_cast<SerializableNode*>(nodesVector[i]->getSerializable(pagePath));
		s->store(pageFiles[pagePath]);
	}
	index.storeIndex();
	closeStreamsOnMap(pageFiles);
}

void Graph::storeSchemaMap() {
	ConfigFileHandler* cfg = getConfigFileHandler(this->databaseName);
	string schemaDir = Database::getDatabase(this->databaseName)->buildSotrePath(this->name, ElementType::SCHEMA, true);
	string pageExtension = (*cfg->configFileMap)[ConfigFileAttrbute::pageExtension];
	string schemaIndexPath = schemaDir + (*cfg->configFileMap)[ConfigFileAttrbute::schemaIndexFile];
	IndexHandler index(schemaIndexPath);
	string pageId = "";
	unordered_map<string, ofstream*> pageFiles;
	string pagePath;
	//if (fileExists(schemaIndexPath))
		//index.loadIndex();
	//else {
		pageId = to_string(index.getNextPageId());
		pagePath = schemaDir + pageId + pageExtension;
		if (pageFiles.find(pagePath) == pageFiles.end()) {
			pageFiles[pagePath] = new ofstream(pagePath, ios::out | ios::binary); //new ofstream(pagePath, ios::out | ios::app | ios::binary);
			long size = this->schemaMap->size();
			char* sizec = (char*)& size;
			unsigned char* c = (unsigned char*)sizec;
			pageFiles[pagePath]->write((char*)& size, sizeof(long));
		}
	//}
	for (unordered_map<long, Schema*>::iterator it = this->schemaMap->begin(); it != this->schemaMap->end(); it++) {
		index.indexMap[to_string(it->second->id)] = pageId;
		it->second->store(pageFiles[pagePath]);
	}
	index.storeIndex();
	closeStreamsOnMap(pageFiles);
}

void Graph::loadVertexMap(vector<Node*> nodeVector, vector<Edge*> edgeVector) {
	if (nodeVector.size() <= 0)
		return;
	ConfigFileHandler* cfg = getConfigFileHandler(this->databaseName);
	string vertexDir = Database::getDatabase(this->databaseName)->buildSotrePath(this->name, ElementType::VERTEX, false);
	string pageExtension = (*cfg->configFileMap)[ConfigFileAttrbute::pageExtension];
	string vertexIndexPath = vertexDir + (*cfg->configFileMap)[ConfigFileAttrbute::vertexIndexFile];
	IndexHandler index(vertexIndexPath);
	if (fileExists(vertexIndexPath))
		index.loadIndex();
	else
		return;
	vector<string> pageIds;
	for (unordered_map<string, string>::iterator it = index.indexMap.begin(); it != index.indexMap.end(); it++) {
		if (find(pageIds.begin(), pageIds.end(), it->second) == pageIds.end())
			pageIds.push_back(it->second);
	}
	for (long i = 0; i < pageIds.size(); i++)
	{
		string path = vertexDir + pageIds[i] + pageExtension;
		ifstream* rf = new ifstream(path, ios::in | ios::binary);
		if (!rf) cout << "HAY PROBLEMAS :( " << endl;
		char* sizec = new char[sizeof(long)];
		rf->read(sizec, sizeof(long));
		unsigned char* c = (unsigned char*)sizec;
		long size = char_ptr_to_int(sizec);
		for (long i = 0; i < size; i++) {
			SerializableVertex s;
			s.load(rf);
			Vertex* v = new Vertex();
			v->id = s.id;
			Node* n = vectorFindById<Node>(nodeVector, new Node(s.node));
			if (n != NULL)
				v->node = n;
			else
				cout << "FAIL: NODE NOT FOUND, ID: " << s.node << endl;
			for (long i = 0; i < s.edgesIdVector.size(); i++)
			{
				Edge* e = vectorFindById<Edge>(edgeVector, new Edge(s.edgesIdVector[i]));
				if (e != NULL)
					v->edgesVector.push_back(e);
				else
					cout << "FAIL: EDGE NOT FOUND, ID: " << s.edgesIdVector[i] << endl;
			}
			this->vertexMap->insert({ n, v });
		}
		rf->close();
		if (!rf->good()) cout << "FAIL CLOSING FILE: " << pageIds[i] << endl;
	}
}

vector<Edge*> Graph::loadEdgeVector(vector<Node*> nodeVector) {
	vector<Edge*> edgeVector;
	ConfigFileHandler* cfg = getConfigFileHandler(this->databaseName);
	string edgeDir = Database::getDatabase(this->databaseName)->buildSotrePath(this->name, ElementType::EDGE, false);
	string pageExtension = (*cfg->configFileMap)[ConfigFileAttrbute::pageExtension];
	string edgeIndexPath = edgeDir + (*cfg->configFileMap)[ConfigFileAttrbute::edgeIndexFile];
	IndexHandler index(edgeIndexPath);
	if (fileExists(edgeIndexPath))
		index.loadIndex();
	else
		return edgeVector;
	vector<string> pageIds;
	for (unordered_map<string, string>::iterator it = index.indexMap.begin(); it != index.indexMap.end(); it++) {
		if (find(pageIds.begin(), pageIds.end(), it->second) == pageIds.end())
			pageIds.push_back(it->second);
	}
	for (long i = 0; i < pageIds.size(); i++)
	{
		string path = edgeDir + pageIds[i] + pageExtension;
		ifstream* rf = new ifstream(path, ios::in | ios::binary);
		if (!rf) cout << "HAY PROBLEMAS :( " << endl;
		char* sizec = new char[sizeof(long)];
		rf->read(sizec, sizeof(long));
		unsigned char* c = (unsigned char*)sizec;
		long size = char_ptr_to_int(sizec);
		for (long i = 0; i < size; i++) {
			SerializableEdge serializable;
			serializable.load(rf);
			Edge* edge = new Edge(serializable);
			Edge* result = vectorFindById<Edge>(edgeVector, edge);
			//Edge* result = vectorFindByFn<Edge>(edgeVector, edge, Edge::compareEdges);
			//bool(*test)(Edge* e, Edge* e2) = Edge::compareEdges;
			if (result == NULL)
				edgeVector.push_back(edge);
			else
				edge = result;
			if (edge->originNode == NULL) {
				Node* originNode = vectorFindById<Node>(nodeVector, new Node(serializable.originNode));
				//Node* originNode = vectorFindByFn<Node>(nodeVector, new Node(serializable.originNode), Node::compareNodes);
				if (originNode == NULL)
					cout << "ERROR! NODO ORIGEN NO ENCONTRADO! ID: "<< serializable.originNode << endl;
				else
					edge->originNode = originNode;
			}

			if (edge->targetNode == NULL) {
				Node* targetNode = vectorFindById<Node>(nodeVector, new Node(serializable.targetNode));
				//Node* targetNode = vectorFindByFn<Node>(nodeVector, new Node(serializable.targetNode), Node::compareNodes);
				if (targetNode == NULL)
					cout << "ERROR! NODO ORIGEN NO ENCONTRADO! ID: " << serializable.targetNode << endl;
				else
					edge->targetNode = targetNode;
			}

			if (edge->schema == NULL) {
				if (this->schemaMap->find(serializable.schemaId) == this->schemaMap->end())
					cout << "EDGE SCHEMA NOT FOUND, id: " << serializable.schemaId << endl;
				else
					edge->schema = this->schemaMap->at(serializable.schemaId);
			}

			if (edge->targetNode == NULL || edge->originNode == NULL)
				edgeVector.pop_back();
		}
		rf->close();
		if (rf->fail()) cout << "loadEdgeVector: fail closing ifstream on file: " << pageIds[i] << endl;
	}
	return edgeVector;
}

vector<Node*> Graph::loadNodeVector() {
	vector<Node*> nodeVector;
	ConfigFileHandler* cfg = getConfigFileHandler(this->databaseName);
	string nodeDir = Database::getDatabase(this->databaseName)->buildSotrePath(this->name, ElementType::NODE, false);
	string pageExtension = (*cfg->configFileMap)[ConfigFileAttrbute::pageExtension];
	string nodeIndexPath = nodeDir + (*cfg->configFileMap)[ConfigFileAttrbute::nodeIndexFile];
	IndexHandler index(nodeIndexPath);
	if (fileExists(nodeIndexPath))
		index.loadIndex();
	else
		return nodeVector;
	vector<string> pageIds;
	for (unordered_map<string, string>::iterator it = index.indexMap.begin(); it != index.indexMap.end(); it++) {
		if (find(pageIds.begin(), pageIds.end(), it->second) == pageIds.end())
			pageIds.push_back(it->second);
	}
	for (long i = 0; i < pageIds.size(); i++)
	{
		string path = nodeDir + pageIds[i] + pageExtension;
		ifstream* rf = new ifstream(path, ios::in | ios::binary);
		if (!rf) cout << "HAY PROBLEMAS :( " << endl;
		char* sizec = new char[sizeof(long)];
		rf->read(sizec, sizeof(long));
		unsigned char* c = (unsigned char*)sizec;
		long size = char_ptr_to_int(sizec);
		for (long i = 0; i < size; i++){
			SerializableNode serializable;
			serializable.load(rf);
			Node* node = new Node(serializable);
			//Node* result = vectorFindById<Node>(nodeVector, node);
			Node* result = vectorFindByFn<Node>(nodeVector, node, *Node::compareNodes);
			if (result == NULL)
				nodeVector.push_back(node);
			else
				node = result;
			if (node->schema == NULL) {
				if (this->schemaMap->find(serializable.schemaId) == this->schemaMap->end())
					cout << "NODE SCHEMA NOT FOUND, id: " << serializable.schemaId << endl;
				else
					node->schema = this->schemaMap->at(serializable.schemaId);
			}
		}
		rf->close();
		if (rf->fail()) cout << "loadNodeVector: fail closing ifstream on file: " << pageIds[i] << endl;
	}
	return nodeVector;
}

void Graph::loadSchemaMap() {
	ConfigFileHandler* cfg = getConfigFileHandler(this->databaseName);
	string schemaDir = Database::getDatabase(this->databaseName)->buildSotrePath(this->name, ElementType::SCHEMA, true);
	string pageExtension = (*cfg->configFileMap)[ConfigFileAttrbute::pageExtension];
	string schemaIndexPath = schemaDir + (*cfg->configFileMap)[ConfigFileAttrbute::schemaIndexFile];
	IndexHandler index(schemaIndexPath);
	if (fileExists(schemaIndexPath))
		index.loadIndex();
	else
		return;
	vector<string> pageIds;
	for (unordered_map<string, string>::iterator it = index.indexMap.begin(); it != index.indexMap.end(); it++) {
		if (find(pageIds.begin(), pageIds.end(), it->second) == pageIds.end())
			pageIds.push_back(it->second);
	}
	for (long i = 0; i < pageIds.size(); i++)
	{
		string path = schemaDir + pageIds[i] + pageExtension;
		ifstream* rf = new ifstream(path, ios::in | ios::binary);
		if (!rf) cout << "HAY PROBLEMAS :( " << endl;
		char* sizec = new char[sizeof(long)];
		rf->read(sizec, sizeof(long));
		unsigned char* c = (unsigned char*)sizec;
		long size = char_ptr_to_int(sizec);
		for (long i = 0; i < size; i++) {
			Schema* schema = new Schema();
			schema->load(rf);
			if (this->schemaMap->find(schema->id) == this->schemaMap->end())
				(*this->schemaMap)[schema->id] = schema;
		}
		rf->close();
		if (rf->fail()) cout << "loadSchemaMap: fail closing ifstream on file: " << pageIds[i] << endl;
	}
}

long Graph::getNextVertexId() {
	long max = 0;
	for (unordered_map<Node*, Vertex*>::iterator it = this->vertexMap->begin(); it != this->vertexMap->end(); it++) {
		if (it->second->id > max)
			max = it->second->id;
	}
	return ++max;
}

long Graph::getNextNodeId() {
	long max = 0;
	for (unordered_map<Node*, Vertex*>::iterator it = this->vertexMap->begin(); it != this->vertexMap->end(); it++) {
		if (it->second->id > max)
			max = it->second->id;
	}
	return ++max;
}

long Graph::getNextEdgeId() {
	long max = 0;
	for (unordered_map<Node*, Vertex*>::iterator it = this->vertexMap->begin(); it != this->vertexMap->end(); it++) {
		for (int i = 0; i < it->second->edgesVector.size(); i++)
		{
			if (it->second->edgesVector[i]->id > max)
				max = it->second->edgesVector[i]->id;
		}
	}
	return ++max;
}

vector<Edge*> Graph::getEdgeVector() {
	vector<Edge*> edgeVector;
	for (unordered_map<Node*, Vertex*>::iterator it = this->vertexMap->begin(); it != this->vertexMap->end(); it++) {
		for (int i = 0; i < it->second->edgesVector.size(); i++)
		{
			edgeVector.push_back(it->second->edgesVector[i]);
		}
	}
	return edgeVector;
}

vector<Node*> Graph::getNodeVector() {
	vector<Node*> nodeVector;
	for (unordered_map<Node*, Vertex*>::iterator it = this->vertexMap->begin(); it != this->vertexMap->end(); it++) {
		nodeVector.push_back(it->first);
	}
	return nodeVector;
}