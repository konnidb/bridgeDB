#ifndef QUERY_STRUCTS
#define QUERY_STRUCTS
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

struct query_struct;
struct node_struct;
struct edge_struct;
struct field_struct;

enum field_type {
    INT_v,
    FLOAT_v,
    DOUBLE_v,
    LONG_v,
    STRING_v,
    BOOL_V
};

union field_value {
    int int_value;
    float float_value;
    double double_value;
    long long_value;
    char* string_value;
    bool bool_value;    
};

struct query_struct {
    char* name;
};

struct node_struct {
    char* name;
    unordered_map<char*, edge_struct*> connected_edges;
    unordered_map<char*, node_struct*> connected_nodes;
    vector<field_struct> assoc_values;
};

struct edge_struct {
    char* name;
    char* label;
    node_struct* origin;
    node_struct* destination;
    vector<field_struct> assoc_values;
};
struct field_struct {
    field_value* value;
    field_type type;
};

#endif