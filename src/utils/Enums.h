#pragma once

enum LogicOperator {
	AND,
	OR,
	NAND,
	NOR,
	NOT
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
	NUM,
	STR,
	BOOL,
	CAT,
	DT
};

enum ConfigFileAttrbute {
	databaseName,
	dataDirectory,
	schemaDirectory,
	nodeDirectory,
	edgeDirectory,
	vertexDirectory,
	schemaIndexFile,
	nodeIndexFile,
	edgeIndexFile,
	vertexIndexFile,
	backupDirectory,
	logDirectory,
	pageExtension
};