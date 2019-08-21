#include<iostream>
#include<unordered_map>
#include<list>
#include<string>
#include"..\..\utils\LogHandler.cpp"
#include"..\utils\Serializable.cpp"
#include"Edge.cpp"
#include"Node.cpp"
using namespace std;

class Graph {
public:
	list<Node*> nodeList;
	int id;
	string name;
};