#include<iostream>
#include <string>
#include<unordered_map>
using namespace std;

enum LogType {
	FAILURE,
	ERROR,
	WARNING,
	INFO,
	SUCCESS
};

class Log {
public:
	int logCode;
	string logName;
	string description;
	LogType logType;
	void(*action)();

	Log(int logCode, string logName, string description, LogType logType, void(*action)()) {
		this->logCode = logCode;
		this->logName = logName;
		this->description = description;
		this->logType = logType;
		this->action = action;
	}
};

class LogActions {
public:
	string logPath; //RESOLVE TO PASS INSTANCE
	static void print(){}
	static void printLog(){}
	static void printAndLog() {}
};

class ErrorMap {
public:
	static Log * error_loading_object;
	static Log * error_storing_object;

};

Log * ErrorMap::error_storing_object = new Log(1001, "", "", FAILURE, &LogActions::printAndLog);
Log * ErrorMap::error_loading_object = new Log(1001, "", "", FAILURE, &LogActions::printAndLog);


