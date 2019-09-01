#include<iostream>
#include<unordered_map>
#include<list>
#include<string>
#include"..\utils\LogHandler.cpp"
#include"..\graph\utils\Serializable.cpp"
#include"..\graph\structs\Graph.cpp"
#include"..\admin\ConfigFileModel.cpp"
using namespace std;

class StoreHandler {
private:
	string directory;
	Serializable * element;

	StoreHandler(Serializable element) {

	}

	void buildPath() {
		if (directory == NULL) {
			directory = ConfigFileModel::
		}
	}
};