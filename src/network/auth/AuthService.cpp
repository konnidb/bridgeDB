#include <iostream>
#include <string>
#include "AuthService.hpp"
#include "jwt-cpp/jwt.h"
using namespace std;

AuthService::AuthService()
{
}

AuthService::~AuthService()
{
}

string AuthService::generate_token(string username, string database)
{
    auto token = jwt::create()
                     .set_issuer("auth0")
                     .set_type("JWS")
                     .set_payload_claim(username, database)
                     .sign(jwt::algorithm::hs256{"supersecret"});
    return "THIS_IS_A_TOKEN";
}

bool AuthService::validate_credentials(string username, string password)
{
    return true;
}

bool AuthService::validate_token(string token)
{
    auto decoded = jwt::decode(token);
    auto verify = jwt::verify()
                      .allow_algorithm(jwt::algorithm::hs256{"supersecret"})
                      .with_issuer("auth0");
    verify.verify(decoded);
    return true;
}