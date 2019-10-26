#pragma once
#include <string>
#include <iostream>
using namespace std;

struct AuthData {
    bool authenticated;
    string database_name;
    string graph_name;
    string username;
};

class AuthService
{
private:
    /* data */
public:
    AuthService();
    static AuthData get_credentials(string token);
    static bool validate_credentials(string username, string password);
    static string generate_token(string, string);
    static bool validate_token(string);
    ~AuthService();
};
