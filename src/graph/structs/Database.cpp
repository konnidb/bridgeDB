#pragma once
#include<iostream>
#include"..\utils\Serializable.h"
#include"Graph.cpp"
using namespace std;

class Database {
	string name;
	list<Graph> graphList;
	int deleteConfig;
};