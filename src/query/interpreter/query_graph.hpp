#pragma once
#include <iostream>
#include <string.h>
#include <vector>
#include <iterator>
#include "Interpreter.hpp"
#include "intr_structs.hpp"
using namespace std;

class query_graph
{
private:
    string* graph_name;
    vector<interpreter_node>* nodes = NULL;
    vector<interpreter_edge>* edges = NULL;
public:
    query_graph(void);
    query_graph(interpreter_node*, interpreter_edge*);
    interpreter_edge* get_edges();
    interpreter_node* get_nodes();
    void set_nodes(interpreter_node*);
    void set_edges(interpreter_edge*);

    void add_node(interpreter_node);
    void add_edge(interpreter_edge);
    void add_node_array(interpreter_node*);
    void add_edge_array(interpreter_edge*);

    void set_graph_name(string);
    void set_graph_name(string*);
    ~query_graph();
};

query_graph::query_graph(void)
{
    this->nodes = new vector<interpreter_node>();
    this->edges = new vector<interpreter_edge>();
}

query_graph::query_graph(interpreter_node* nodes, interpreter_edge* edges)
{
    int nodes_size = sizeof(nodes) / sizeof(nodes[0]);
    int edges_size = sizeof(edges) / sizeof(edges[0]);
    this->nodes = new vector<interpreter_node>(nodes, nodes + nodes_size);
    this->edges = new vector<interpreter_edge>(edges, edges + edges_size);
}

query_graph::~query_graph()
{
    delete this->edges;
    delete this->nodes;
}

void query_graph::set_edges(interpreter_edge* edges)
{
    
}

void query_graph::set_nodes(interpreter_node *nodes)
{
    
}

void query_graph::add_node_array(interpreter_node *node_array)
{
    int size = sizeof(node_array) / sizeof(node_array[0]);
    // this->nodes->insert(nodes->begin)
}

void query_graph::add_edge_array(interpreter_edge *edge_array)
{
       
}

void query_graph::set_graph_name(string name)
{
    this->graph_name = &name;
}

void query_graph::set_graph_name(string* name)
{
    this->graph_name = name;
}
