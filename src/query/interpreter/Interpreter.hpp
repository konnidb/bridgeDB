#include <iostream>
#include <string.h>
#include <unordered_map>
using namespace std;

#ifndef INTERPRETER_CLASS
#define INTERPRETER_CLASS

class Interpreter
{
private:
  int parser_result = 0;
  bool is_inside_match;
  string query;
  unordered_map<string, string> nodes;
  unordered_map<string, string> node_alias;
  unordered_map<string, string> matched_nodes;
  unordered_map<string, string> edges;
  unordered_map<string, string> edge_alias;

public:
  Interpreter(string query);
  void match(void);
  void return_clause(void);
  void create_node_id(string);
  string get_query(void);
  void set_parse_result(int);
  int get_parse_result(void);
  void parse_query(void);
  ~Interpreter();
};
#endif