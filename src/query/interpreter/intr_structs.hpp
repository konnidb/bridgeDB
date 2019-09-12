#pragma once
#include <iostream>
#include <unordered_map>
using namespace std;

struct interpreter_struct {
public:	
	char* name;
	char* schema_name;
	unordered_map<string, void*>* values;
};

struct interpreter_edge: public interpreter_struct
{
	public:
	interpreter_struct* source;
	interpreter_struct* destination;
	char *label;
};

struct interpreter_node: public interpreter_struct
{
	public:
	interpreter_edge* edges;
	interpreter_struct* connections; // Array of nodes/edges
};