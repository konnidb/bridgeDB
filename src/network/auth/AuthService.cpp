#include <iostream>
#include <string>
#include "AuthService.hpp"
#include "jwt-cpp/jwt.h"

AuthService::AuthService()
{
}

AuthService::~AuthService()
{
}

std::string AuthService::generate_token(std::string username, std::string database)
{
    auto c_username = username.c_str();
    auto c_database = database.c_str();
    auto token = jwt::create()
                     .set_issuer("auth0")
                     .set_type("JWS")
                     .set_payload_claim(c_username, jwt::claim(std::string("username")))
                     .set_payload_claim(c_database, jwt::claim(std::string("database")))
                     //  .set_payload_claim(c_username, std::string("username"))
                     //  .set_payload_claim("database", std::std::string("database"))
                     .sign(jwt::algorithm::hs256{"supersecret"});
    return token;
}

bool AuthService::validate_credentials(std::string username, std::string password)
{
    return true;
}

bool AuthService::validate_token(std::string token)
{
    auto decoded = jwt::decode(token);
    auto verify = jwt::verify()
                      .allow_algorithm(jwt::algorithm::hs256{"supersecret"})
                      .with_issuer("auth0");
    verify.verify(decoded);
    return true;
}