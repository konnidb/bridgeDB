#pragma once
/*#include<iostream>
#include<string>
#include<unordered_map>

using namespace std;


const char ELMNT_SEPARATOR = '~';
const char PROP_SEPARATOR = '¬';

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

	for (int i = 0; i < properties.length(); i++)
	{
		if (properties[i] == PROP_SEPARATOR) {
			cout << "ENTRA PROPS SEPARATOR" << properties[i] << endl;
			propertiesVector.push_back(prop);
			prop = "";
		}
		else
			prop += properties[i];
	}


	for (int i = 0; i < propertiesVector.size(); i++)
	{
		string key = "";
		string tmp = "";
		for (int j = 0; j < propertiesVector[i].length(); j++)
		{
			if (propertiesVector[i][j] == ELMNT_SEPARATOR) {
				key = tmp;
				tmp = "";
			}
			else
				tmp += propertiesVector[i][j];
		}
		cout << "key : " << key << " Value: " << tmp;
		output[key] = tmp;
	}
	cout << "OUTPUT SIZE: " << output.size() << endl;
	return output;
}*/