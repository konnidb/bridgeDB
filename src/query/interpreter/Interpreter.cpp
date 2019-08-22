#include <iostream>
#include <string.h>
#include <unordered_map>
#include "Interpreter.hpp"

using namespace std;

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
	string nv;
	this->nodes[node_id] = nv;
	// *this->nodes->insert(make_pair(node_id, NULL));
}

void Interpreter::set_parse_result(int result)
{
	this->parser_result = result;
}

int Interpreter::get_parse_result(void)
{
	return this->parser_result;
}

void Interpreter::parse_query(void)
{

}

Interpreter::Interpreter(string query)
{
	this->query = query;
}

Interpreter::~Interpreter()
{
}
