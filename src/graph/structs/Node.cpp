#include<iostream>
#include<unordered_map>
#include<list>
#include<string>
#include"..\..\utils\LogHandler.cpp"
#include"..\utils\Serializable.cpp"
#include"Edge.cpp"
using namespace std;

class Node : Serializable {
public:
	list<Edge> edgesList;
};