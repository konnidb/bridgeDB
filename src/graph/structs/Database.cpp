#pragma once
#include<iostream>
//#include"..\utils\Serializable.h"
#include"Graph.cpp"
using namespace std;

class Database {
public:
	string name;
	vector<Graph*> graphVector;
	int deleteConfig;
};