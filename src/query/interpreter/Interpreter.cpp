#include <iostream>
#include <string.h>
#include <unordered_map>
#include "Interpreter.hpp"
#include "query_graph.hpp"

using namespace std;

void Interpreter::create_edge_id(string edge_id)
{
	this->edges[edge_id] = NULL;
}

void Interpreter::create_edge_alias(string alias, string edge_id)
{
	this->edge_alias[alias] = edge_id;
}

void Interpreter::assign_edge_value(string node_id, interpreter_edge* parameter)
{
	this->edges[node_id] = parameter;
}

unordered_map<string, interpreter_node*> Interpreter::get_nodes_map(void)
{
	return this->nodes;
}

interpreter_node* Interpreter::get_node_value(string node_id)
{
	return nodes[node_id];
}

interpreter_node* Interpreter::get_node_value_by_alias(string alias)
{
	string node_id = node_alias[alias];
	return nodes[node_id];
}
unordered_map<string, interpreter_edge*> Interpreter::get_edges_map(void)
{
	return edges;
}

interpreter_edge* Interpreter::get_edge_value(string edge_id)
{
	return edges[edge_id];
}

interpreter_edge* Interpreter::get_edge_value_by_alias(string alias)
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
	this->nodes[node_id] = NULL;
	// *this->nodes->insert(make_pair(node_id, NULL));
}

void Interpreter::create_node_id(char* node_id)
{
	string id(node_id);
	cout<<node_id <<endl<<endl<<endl;
	this->nodes[id] = NULL;
}

void Interpreter::set_node_id_value(char* node_id, interpreter_node* value)
{
	string id(node_id);
	this->nodes[id] = value;
}

void Interpreter::set_node_id_value(string node_id, interpreter_node* value)
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
	this->graph = new query_graph();
	this->query = query;
}

Interpreter::Interpreter(string query, string graph_name)
{
	this->graph = new query_graph();
	this->graph->set_graph_name(graph_name);
	this->query = query;
}

Interpreter::~Interpreter()
{
}
