#include<iostream>
#include<unordered_map>
#include<fstream>
#include<string>
#include"..\..\utils\LogHandler.cpp"
using namespace std;

enum ElementType {
	NODE,
	EDGE,
	SCHEMA,
	UNDEF
};

class Serializable {
public:
	unordered_map<string, string> properties;
	int id;
	string path;
	const ElementType objType;

	Serializable(): objType(UNDEF){}
	Serializable(string path): objType(UNDEF) {
		this->path = path;
	}



	void load(string contentStr) {
		ifstream rf("student.dat", ios::out | ios::binary);
		if (!rf) ErrorMap::error_loading_object->action();
		Serializable deserialized;
		rf.read((char *)&deserialized, sizeof(Serializable));
		rf.close();
		if (!rf.good()) ErrorMap::error_loading_object->action();
		this->properties = deserialized.properties;
		this->path = deserialized.path;
	}

	string store() {
		ofstream wf(this->path, ios::out | ios::binary);
		if (!wf) ErrorMap::error_storing_object->action();
		wf.write((char *) this, sizeof(Serializable));
		wf.close();
		if (!wf.good()) ErrorMap::error_storing_object->action();
	}
};

