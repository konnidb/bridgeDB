#pragma once
#include<iostream>
#include<list>
using namespace std;

class IndexHandler {
public:
	string directory;
	list<IndexModel> indexes;
	IndexHandler(string directory){}
	void loadIndex(){}

};

class IndexModel {
public:
	int id;
	string page;
	int grouperField = NULL;
	int grouperContent = NULL;
};