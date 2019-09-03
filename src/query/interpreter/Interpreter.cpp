#include <iostream>
#include <string.h>
#include <unordered_map>
#include "Interpreter.hpp"

using namespace std;

void Interpreter::create_edge_id(string edge_id)
{
	this->edges[edge_id] = NULL;
}

void Interpreter::create_edge_alias(string alias, string edge_id)
{
	this->edge_alias[alias] = edge_id;
}

void Interpreter::assign_edge_value(string node_id, void* parameter)
{
	this->nodes[node_id] = parameter;
}

unordered_map<string, void *> Interpreter::get_nodes_map(void)
{
	return this->nodes;
}

void* Interpreter::get_node_value(string node_id)
{
	return nodes[node_id];
}

void* Interpreter::get_node_value_by_alias(string alias)
{
	string node_id = node_alias[alias];
	return nodes[node_id];
}
unordered_map<string, void *> Interpreter::get_edges_map(void)
{
	return edges;
}

void* Interpreter::get_edge_value(string edge_id)
{
	return edges[edge_id];
}

void* Interpreter::get_edge_value_by_alias(string alias)
{
	string edge_id = edge_alias[alias];
	return edges[edge_id];
}

string Interpreter::get_query(void)
{
	return this->query;
}

void Interpreter::return_clause(void)
{
	this->is_inside_match = false;
}

void Interpreter::match(void)
{
	this->is_inside_match = true;
}

void Interpreter::create_node_id(string node_id)
{
	cout<<"In this line";
	string nv = NULL;
	this->nodes[node_id] = &nv;
	// *this->nodes->insert(make_pair(node_id, NULL));
}

void Interpreter::create_node_id(char* node_id)
{
	string id(node_id);
	cout<<node_id <<endl<<endl<<endl;
	this->nodes[id] = &id;
}

void Interpreter::set_node_id_value(char* node_id, void* value)
{
	string id(node_id);
	this->nodes[id] = value;
}

void Interpreter::set_node_id_value(string node_id, void* value)
{
	this->nodes[node_id] = value;
}

void Interpreter::set_parse_result(int result)
{
	this->parser_result = result;
}

int Interpreter::get_parse_result(void)
{
	return this->parser_result;
}

Interpreter::Interpreter(string query)
{
	this->query = query;
}

Interpreter::~Interpreter()
{
}
