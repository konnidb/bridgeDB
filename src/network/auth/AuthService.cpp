#include <iostream>
#include <string>
#include "AuthService.hpp"
using namespace std;

AuthService::AuthService()
{
}

AuthService::~AuthService()
{
}

string AuthService::generate_token()
{
    return "THIS_IS_A_TOKEN";
}

bool AuthService::validate_credentials(string username, string password)
{
    return true;
}

bool AuthService::validate_token(string token)
{
    return true;
}