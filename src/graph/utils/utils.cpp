#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<unordered_map>
#include"..\..\utils\Enums.h"
#include"..\structs\Database.h"
#include<math.h>

using namespace std;


const char ELMNT_SEPARATOR = '~';
const char PROP_SEPARATOR = '¬';

int char_ptr_to_int(char* c) {
	unsigned char* uc = (unsigned char*)c;
	int result = 0;
	for (int i = 0; i < sizeof(uc); i++){
		result += uc[i] * pow(256, i);
	}
	return result;
}
/*
template <class T >
T* vectorFindByFn(vector<T*> vectorEvl, T* elmnt, bool (*compareFn)(T* elmnt1, T* elmnt2)) {
	for (int i = 0; i < vectorEvl.size(); i++)
	{
		if (compareFn(elmnt, vectorEvl[i]))
			return vectorEvl[i];
	}
	return NULL;
}


template<class T>
T* vectorFindById(vector<T*> vectorEvl, T* elmnt) {
	for (int i = 0; i < vectorEvl.size(); i++)
	{
		if (elmnt->id == vectorEvl[i]->id)
			return vectorEvl[i];
	}
	return NULL;
}
*/

string serializeMap(unordered_map<string, string> properties) {
	string strBuilder = "";
	for (unordered_map<string, string>::iterator it = properties.begin(); it != properties.end(); it++) {
		strBuilder += it->first + ELMNT_SEPARATOR + it->second + PROP_SEPARATOR;
	}
	return strBuilder;
}

unordered_map<string, string> deserializeMap(string properties) {
	unordered_map<string, string> output;
	vector<string> propertiesVector;
	string prop = "";

	for (int i = 0; i < properties.length(); i++){
		if ((int)properties[i] == 0)
			continue;
		if (properties[i] == PROP_SEPARATOR) {
			propertiesVector.push_back(prop);
			prop = "";
		}
		else
			prop += properties[i];
	}

	for (int i = 0; i < propertiesVector.size(); i++){
		string key = "";
		string tmp = "";
		for (int j = 0; j < propertiesVector[i].length(); j++){
			if (propertiesVector[i][j] == ELMNT_SEPARATOR) {
				key = tmp;
				tmp = "";
			}
			else
				tmp += propertiesVector[i][j];
		}
		//cout << "key : " << key << " Value: " << tmp;
		output[key] = tmp;
	}
	cout << "OUTPUT SIZE: " << output.size() << endl;
	return output;
}

bool fileExists(string path){
	fstream stream;
	stream.open(path);
	if (stream.fail())
		return false;
	stream.close();
	return true;
}

ConfigFileHandler* getConfigFileHandler(string databaseName) {
	Database db = Database::getDatabase(databaseName);
	return db.cfg;
}
/*
string buildIndexPath(string databaseName, ElementType element) {
	Database db = Database::getDatabase(databaseName);
	string directory, indexFile;
	switch (element) {
		case ElementType::EDGE:
			directory = db.cfg->configFileMap[ConfigFileAttrbute::edgeDirectory];
			indexFile = db.cfg->configFileMap[ConfigFileAttrbute::edgeIndexFile];
			break;
		case ElementType::NODE:
			directory = db.cfg->configFileMap[ConfigFileAttrbute::nodeDirectory];
			indexFile = db.cfg->configFileMap[ConfigFileAttrbute::nodeIndexFile];
			break;
		case ElementType::SCHEMA:
			break;
		case ElementType::VERTEX:
			directory = db.cfg->configFileMap[ConfigFileAttrbute::vertexDirectory];
			indexFile = db.cfg->configFileMap[ConfigFileAttrbute::vertexIndexFile];
			break;
	}
	return directory + indexFile;
}
*/