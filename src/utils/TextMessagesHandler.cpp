#include<iostream>
#include<unordered_map>
#include<string>
#include"LogHandler.h"

using namespace std;

class TextMessages {
public:
	unordered_map<string, Log> init;
	unordered_map<string, Log> end;
	unordered_map<string, Log> storageError;
};

class TextMessageHandler {
public:
	void LoadTextMessages();
};