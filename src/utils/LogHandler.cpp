#pragma once
#include<iostream>
#include<string>
#include<unordered_map>
#include"LogHandler.h"
using namespace std;


Log::Log(long logCode, string logName, string description, LogType logType, void(*action)()) {
	this->logCode = logCode;
	this->logName = logName;
	this->description = description;
	this->logType = logType;
	this->action = action;
}

void LogActions::print() {}
void LogActions::printLog() {}
void LogActions::printAndLog() {}

//Log * ErrorMap::error_storing_object  = Log(1001, "", "", FAILURE, &LogActions::printAndLog);
//Log * ErrorMap::error_loading_object = Log(1001, "", "", FAILURE, &LogActions::printAndLog);


