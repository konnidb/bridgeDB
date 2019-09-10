#pragma once
#include<iostream>
#include<unordered_map>
#include<string>
//#include"..\utils\LogHandler.cpp"
#include"..\graph\utils\Serializable.h"
#include"..\graph\structs\Graph.cpp"
#include"..\admin\ConfigFile.cpp"
using namespace std;

class StoreHandler {
private:
	string directory;
	Serializable * element;

	StoreHandler(Serializable element) {

	}

	void buildPath() {
		if (directory.length()==0) {
			//directory = ConfigFileModel::dataDirectory;
		}
		//return directory.append(element->objType);
	}

	void loadIndex(){}

	void loadPage(){}

};