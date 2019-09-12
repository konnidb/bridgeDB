#pragma once
#include <iostream>
#include <string.h>
#include <unordered_map>
#include "query_graph.hpp"
using namespace std;

class Interpreter
{
private:
	int parser_result = 0;
	bool is_inside_match;
	string query;
	unordered_map<string, interpreter_node*> nodes;
	unordered_map<string, interpreter_node*> matched_nodes;
	unordered_map<string, string> node_alias;
	unordered_map<string, interpreter_edge*> edges;
	unordered_map<string, interpreter_edge*> matcher_edges;
	unordered_map<string, string> edge_alias;
	query_graph* graph;
public:
	char* element = "1231313";
	Interpreter(string query);
	Interpreter(string query, string graph_name);
	void match(void);
	void return_clause(void);
	void create_node_id(string);
	void create_node_id(char *);
	void create_node_alias(string, string);
	void assign_node_value(string, interpreter_node *);
	void create_edge_id(string);
	void create_edge_alias(string, string);
	void assign_edge_value(string, interpreter_edge*);
	void set_node_id_value(char*, interpreter_node*);
	void set_node_id_value(string, interpreter_node*);
	string get_query(void);
	void set_parse_result(int);
	int get_parse_result(void);
	// Getters
	unordered_map<string, interpreter_node*> get_nodes_map(void);
	interpreter_node* get_node_value(string);
	interpreter_node* get_node_value_by_alias(string);
	unordered_map<string, interpreter_edge*> get_edges_map(void);
	interpreter_edge* get_edge_value(string);
	interpreter_edge* get_edge_value_by_alias(string);
	~Interpreter();
};
// #endif