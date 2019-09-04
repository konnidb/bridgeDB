#pragma once
#include <iostream>
#include <string.h>
#include <vector>
#include <unordered_map>

using namespace std;

class result_model
{
private:
    unordered_map<string, vector<void*>*>* node_result_sets;
    unordered_map<string, vector<void*>*>* edge_result_sets;
public:
    result_model(/* args */);
    void assign_result_to_node(string, vector<void*>*);
    void assign_result_to_edge(string, vector<void*>*);
    vector<void*> get_result_from_node_id(string);
    vector<void*> get_result_from_edge_id(string);
    ~result_model();
};
