#include<iostream>
#include<string>
#include<fstream>
#include<unordered_map>
#include"../../utils/Enums.h"
#include"../structs/Database.h"
#include"Comparison.h"
#include<math.h>
#include <vector>

using namespace std;


const char ELMNT_SEPARATOR = '~';
const char PROP_SEPARATOR = '�';

long char_ptr_to_int(char* c) {
	unsigned char* uc = (unsigned char*)c;
	long result = 0;
	for (long i = 0; i < sizeof(uc); i++){
		result += uc[i] * pow(256, i);
	}
	return result;
}

bool map_eval_values(unordered_map<string, string> properties, vector<Comparison> toMatch) {
	bool result = NULL;
	for (int i = 0; i < toMatch.size(); i++)
	{
		if (properties.find(toMatch[i].key) != properties.end()) {
			double n1 = NULL;
			double n2 = NULL;
			if (toMatch[i].dataType == DataType::NUM) {
				n1 = stod(toMatch[i].value);
				n2 = stod(properties[toMatch[i].key]);
			}
			bool localRes = false;
			switch (toMatch[i].comparisonOperator) {
				case ComparisonOperator::DF: //number or string
					if (n1 != NULL && n2 != NULL) {
						if (n1 != n2)
							localRes = true;
					}
					else
						if (toMatch[i].value.compare(properties[toMatch[i].key]) != 0)
							localRes = true;
					break;
				case ComparisonOperator::EQ: //number or string
					if (n1 != NULL && n2 != NULL) {
						if (n1 == n2)
							localRes = true;
					}else
						if(toMatch[i].value.compare(properties[toMatch[i].key])==0)
							localRes = true;
					break;
				case ComparisonOperator::GE: //number
					if (n1 >= n2)
						localRes = true;
					break;
				case ComparisonOperator::GT: //number
					if (n1 > n2)
						localRes = true;
					break;
				case ComparisonOperator::LE: //number
					if (n1 <= n2)
						localRes = true;
					break;
				case ComparisonOperator::LT: //number
					if (n1 < n2)
						localRes = true;
					break;
				//case ComparisonOperator::RX: //string
				//	break;
			}
			if (result == NULL)
				result = localRes;
			switch (toMatch[i].logicOperator) {
				case LogicOperator::AND:
					result = result && localRes;
					break;
				case LogicOperator::NAND:
					result = !(result && localRes);
					break;
				case LogicOperator::NONE:
					result = localRes;
					break;
				case LogicOperator::NOR:
					result = !(result || localRes);
					break;
				case LogicOperator::NOT:
					result = false == localRes;
					break;
				case LogicOperator::OR:
					result = result || localRes;
					break;
			}
			if (!result)
				return false;
		}
		else
			return false;
	}
	return true;
}

bool map_contains_values(unordered_map<string, string> properties, unordered_map<string, string> toMatch) {
	if (toMatch.size() <= 0) return false;
	for (unordered_map<string, string>::iterator it = toMatch.begin(); it != toMatch.end(); it++) {
		if (properties.find(it->first) != properties.end()){
			if (toMatch[it->first].compare(properties[it->first]) != 0)
				return false;
		}
		else
			return false;

	}
	return true;
}

/*
template <class T >
T* vectorFindByFn(vector<T*> vectorEvl, T* elmnt, bool (*compareFn)(T* elmnt1, T* elmnt2)) {
	for (long i = 0; i < vectorEvl.size(); i++)
	{
		if (compareFn(elmnt, vectorEvl[i]))
			return vectorEvl[i];
	}
	return NULL;
}


template<class T>
T* vectorFindById(vector<T*> vectorEvl, T* elmnt) {
	for (long i = 0; i < vectorEvl.size(); i++)
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

	for (long i = 0; i < properties.length(); i++){
		if ((int)properties[i] == 0)
			continue;
		if (properties[i] == PROP_SEPARATOR) {
			propertiesVector.push_back(prop);
			prop = "";
		}
		else
			prop += properties[i];
	}

	for (long i = 0; i < propertiesVector.size(); i++){
		string key = "";
		string tmp = "";
		for (long j = 0; j < propertiesVector[i].length(); j++){
			if (propertiesVector[i][j] == ELMNT_SEPARATOR) {
				key = tmp;
				tmp = "";
			}
			else
				tmp += propertiesVector[i][j];
		}
		output[key] = tmp;
	}
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