#include <iostream>
#include <string.h>
#include <unordered_map>
using namespace std;

union node_value {
	int i_value;
	float dec_value;
	string *str_value;
};

class Interpreter
{
private:
	bool is_inside_match;
	string query;
	unordered_map<string, node_value> nodes;
	unordered_map<string, node_value> node_alias;
	unordered_map<string, node_value> matched_nodes;
	unordered_map<string, string> edges;
	unordered_map<string, string> edge_alias;

public:
	Interpreter(string query);
	void match(void);
	void return_clause(void);
	void create_node_id(string);
	string get_query(void);
	~Interpreter();
};

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
	node_value nv;
	this->nodes[node_id] = nv;
	// *this->nodes->insert(make_pair(node_id, NULL));
}

Interpreter::Interpreter(string query)
{
	this->query = query;
	// this->node_alias = new unordered_map<string, node_value>();
	// this->nodes = new unordered_map<string, node_value>();
	// this->edges = new unordered_map<string, string>();
	// this->edge_alias = new unordered_map<string, string>();
}

Interpreter::~Interpreter()
{
}
