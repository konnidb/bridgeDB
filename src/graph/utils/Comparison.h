#pragma once
#include<string>
#include<iostream>
#include"..\..\utils\Enums.h"

using namespace std;

class Comparison {
public:
	ComparisonOperator comparisonOperator;
	LogicOperator logicOperator;
	string key;
	string value;
	DataType dataType;
	Comparison(ComparisonOperator comparisonOperator, LogicOperator logicOperator, string key, string value, DataType); 
	//validate if logicOp and compOp are compatibles
	//validate that NOT and NONE can be just used on first stmnt of list
};