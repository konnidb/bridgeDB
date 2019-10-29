#pragma once
#include <string>
#include <iostream>
#include <vector>
using namespace std;

struct AuthData {
    bool authenticated;
    bool is_root;
    string database_name;
    string graph_name;
    string username;
};

struct AuthCredentials {
    string username, password, database, graph;
};

struct AuthVectorWrapper {
    vector<AuthCredentials> data;
};

class AuthService
{
private:
    /* data */
public:
    AuthService();
    static AuthData get_auth_data(string token);
    static bool validate_credentials(AuthCredentials);
    static string generate_token(AuthCredentials    );
    static bool validate_token(string);
    static bool create_user(AuthCredentials, AuthData);
    static AuthCredentials get_stored_user(string, string);
    static void configurate_auth_file();
    ~AuthService();
};
