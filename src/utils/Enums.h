#pragma once

enum LogicOperator {
	AND,
	OR,
	NAND,
	NOR,
	NOT,
	NONE
};

enum LogType {
	FAILURE_,
	ERROR_,
	WARNING_,
	INFO_,
	SUCCESS_
};

enum ElementType {
	NODE,
	EDGE,
	VERTEX,
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
	NUM_,
	STR_,
	BOOL_,
	CAT_,
	DATETIME_
};

enum ConfigFileAttrbute {
	databaseName,
	storeDirectory,
	schemaIndexFile,
	nodeIndexFile,
	edgeIndexFile,
	vertexIndexFile,
	backupDirectory,
	logDirectory,
	pageExtension,
	graphList
};