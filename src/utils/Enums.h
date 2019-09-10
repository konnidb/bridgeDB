#pragma once

enum LogicOperator {
	AND,
	OR,
	NAND,
	NOR,
	N
};

enum LogType {
	FAILURE,
	ERROR,
	WARNING,
	INFO,
	SUCCESS
};

enum ElementType {
	NODE,
	EDGE,
	SCHEMA,
	GROUP,
	UNDEF
};

enum ComparisonOperator {
	EQ, //equals
	DF, //different
	GT, //great than
	GE, //great or equals than
	LT, //less than
	LE, //less or equals than
	RX //regex
};

enum DataType {
	NUM,
	STR,
	BOOL,
	CAT,
	DT
};