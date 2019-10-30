#pragma once
#include<iostream>
#include<string>
#include<fstream>
#ifdef _WIN32
#include<Windows.h>
#else
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h> 
#endif
#include<unordered_map>
#include"..\..\utils\Enums.h"
#include"..\structs\Database.h"
#include"Comparison.h"
#include<math.h>

using namespace std;


const char LIST_SEPARATOR = (char) 35; //#
const char ELMNT_SEPARATOR = (char) 126; //~
const char PROP_SEPARATOR = (char) 170; //¬

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
			if (toMatch[i].dataType == DataType::NUM_) {
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

string vector_to_str(vector<string> input, char separator) {
	string str_builder = "";
	for (long i = 0; i < input.size(); i++)
	{
		if (i != 0)
			str_builder += separator;
		str_builder += input[i];
	}
	return str_builder;
}

string vector_to_str(vector<string> input) {
	return vector_to_str(input, LIST_SEPARATOR);
}

vector<string> str_to_vector(string input, char separator) {
	vector<string> output;
	string tmp = "";

	for (long i = 0; i < input.length(); i++) {
		if ((int)input[i] == 0)
			continue;
		if (input[i] == separator) {
			output.push_back(tmp);
			tmp = "";
		}
		else
			tmp += input[i];
	}
	if(tmp.length()>0)
		output.push_back(tmp);
	return output;
}

vector<string> str_to_vector(string input) {
	return str_to_vector(input, LIST_SEPARATOR);
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
	Database* db = Database::getDatabase(databaseName);
	return db->cfg;
}

bool dirExists(string dir) {
#ifdef _WIN32
	if (GetFileAttributesA(dir.c_str()) & FILE_ATTRIBUTE_DIRECTORY)
		return true;
#else
	cout << "SHIT GOING ON HERE" << endl;
	struct stat info;

	if (stat(dir.c_str(), &info) != 0) {
		cout << "cannot access" << endl;
		return false;
}
	else if (info.st_mode & S_IFDIR) {
		cout << dir << " Is directory" << endl;
		return true;
	}
	else {
		cout << dir << " Is not directory" << endl;
	}
#endif
	return false;
}


void createSubDir(string dir) {
	//if (dirExists(dir)) return;
#ifdef _WIN32
	if (!CreateDirectory(dir.c_str(), NULL) && ERROR_ALREADY_EXISTS != GetLastError())
		throw "Directory " + dir + " could not be created.";
#else
	if (mkdir(dir.c_str(), 0777) == -1) {
		cout << "mkdir failed" << endl;
		throw "Directory " + dir + " could not be created.";
	}
#endif
}