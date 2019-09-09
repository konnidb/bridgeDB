#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
#include "match_clause.cpp"
using namespace std;

class query_manager
{
private:
    char* query;
    unordered_map<char*, node_struct*>* nodes_map;
    unordered_map<char*, edge_struct*>* edges_map;
    vector<node_struct*>* nodes_vector;
    vector<edge_struct*>* edges_vector;
    bool inside_match = false;
    bool inside_create = false;
    bool inside_where = false;
    bool inside_return = false;
    bool inside_update = false;
    bool inside_delete = false;
public:
    query_manager() {
        this->edges_map = new unordered_map<char*, edge_struct*>();
        this->nodes_map = new unordered_map<char*, node_struct*>();
        this->edges_vector = new vector<edge_struct*>();
        this->nodes_vector = new vector<node_struct*>();
    };
    // Getters / Setters
    char* get_query(void) { return query; };
    void set_query(char* query) { this->query = query; };
    unordered_map<char*, node_struct*>* get_nodes_map(void){ return nodes_map; };
    unordered_map<char*, edge_struct*>* get_edges_map(void){ return edges_map; };

    vector<node_struct*>* get_nodes_vector(void){ return nodes_vector; };
    vector<edge_struct*>* get_edges_vector(void){ return edges_vector; };

    node_struct* get_node_struct_by_name(char* name) { 
        unordered_map<char*, node_struct*> map = *nodes_map;
        return map[name];
    };
    edge_struct* get_edge_struct_by_name(char* name) { 
        unordered_map<char*, edge_struct*> map = *edges_map;
        return map[name];
    };

    bool is_inside_match(void) { return inside_match; };
    void set_inside_match(bool flag) { inside_match = flag; };

    void add_node(node_struct* node) {
        unordered_map<char*, node_struct*> nodes_map = *this->nodes_map;
        nodes_map[node->name] = node;
        nodes_vector->insert(nodes_vector->begin(), node);
    };
    void add_edge(edge_struct* edge) {
        unordered_map<char*, edge_struct*> edges_map = *this->edges_map;
        edges_map[edge->name] = edge;
        edges_vector->insert(edges_vector->begin(), edge);
    };

    void add_connected_edge_to_node(node_struct* node, edge_struct* edge){
        node->connected_edges[edge->name] = edge;
    };
    
    void assign_nodes_to_edge(edge_struct* edge, node_struct* origin, node_struct* destination){
        edge->origin = origin;
        edge->destination = destination;
    };

    void add_assoc_value_to_node(field_struct* field, node_struct* node) {
        node->assoc_values.insert(node->assoc_values.begin(), *field);
    };

    void add_assoc_value_to_edge(field_struct* field, edge_struct* edge) {
        edge->assoc_values.insert(edge->assoc_values.begin(), *field);
    };

    ~query_manager(){};
};

query_manager* qm;

extern "C"
{
    void initialize_query_manager(char* query){
        qm = new query_manager();
        qm->set_query(query);
    }
    char* get_query(void) {
        return qm->get_query();
    }

    void set_query(char* query) {
        qm->set_query(query);
    }

    void set_inside_match(bool flag) {
        qm->set_inside_match(flag);
    }

    node_struct* get_node_struct_by_name(char* name) { 
        return qm->get_node_struct_by_name(name);
    };
    edge_struct* get_edge_struct_by_name(char* name) { 
        return qm->get_edge_struct_by_name(name);
    };

    void add_node(node_struct* node) {
        qm->add_node(node);
    };
    void add_edge(edge_struct* edge) {
        qm->add_edge(edge);
    };

    void add_connected_edge_to_node(node_struct* node, edge_struct* edge){
        qm->add_connected_edge_to_node(node, edge);
    };
    
    void assign_nodes_to_edge(edge_struct* edge, node_struct* origin, node_struct* destination){
        qm->assign_nodes_to_edge(edge, origin, destination);
    };

    void add_assoc_value_to_node(field_struct* field, node_struct* node) {
        qm->add_assoc_value_to_node(field, node);
    };

}
