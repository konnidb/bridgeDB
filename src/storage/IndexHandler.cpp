#pragma once
#include<iostream>
#include<vector>
using namespace std;

class IndexModel {
public:
	int id;
	string page;
	int grouperField = NULL;
	int grouperContent = NULL;
};

class IndexHandler {
public:
	string directory;
	vector<IndexModel> indexes;
	IndexHandler(string directory) {}
	void loadIndex() {}

};