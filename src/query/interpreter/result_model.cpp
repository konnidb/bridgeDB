#include "result_model.hpp"
#include <iostream>
#include <string.h>
#include <unordered_map>
#include <vector>

void result_model::assign_result_to_node(string node_id, vector<void *> *node)
{
    *this->node_result_sets[node_id] = node;
}

void result_model::assign_result_to_edge(string, vector<void *> *)
{

}

vector<void *> *result_model::get_result_from_node_id(string)
{
}

vector<void *> *result_model::get_result_from_edge_id(string)
{
}

result_model::result_model(/* args */)
{
    this->edge_result_sets = new unordered_map<string, void *>();
    this->node_result_sets = new unordered_map<stirng, void *>();
}

result_model::~result_model()
{
    delete this->node_result_sets;
    delete this->edge_result_sets;
}
