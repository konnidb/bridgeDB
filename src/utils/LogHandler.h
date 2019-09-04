#pragma once
#include<iostream>
#include<string>
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

	Log(int logCode, string logName, string description, LogType logType, void(*action)());
};

class LogActions {
public:
	string logPath; //RESOLVE TO PASS INSTANCE
	static void print();
	static void printLog();
	static void printAndLog();
};

class ErrorMap {
public:
	static Log * error_loading_object;
	static Log * error_storing_object;

};