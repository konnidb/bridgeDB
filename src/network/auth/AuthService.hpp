#pragma once
#include <string>
#include <iostream>
using namespace std;

class AuthService
{
private:
    /* data */
public:
    AuthService();
    bool validate_credentials(string username, string password);
    string generate_token(string, string);
    bool validate_token(string);
    ~AuthService();
};