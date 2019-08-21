#include<iostream>
#include<unordered_map>
#include<list>
#include<string>
#include"..\..\utils\LogHandler.cpp"
#include"..\utils\Serializable.cpp"
#include"Edge.cpp"
using namespace std;

class NodeSerializable : Serializable {
public:
	list<int> edgesIdList;
	NodeSerializable(): objType(NODE) {}
};

class Node {
public:
	list<Edge*> edgesList;
	NodeSerializable getSerializable(){}
};