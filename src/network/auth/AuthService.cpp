#include <iostream>
#include <set>
#include <string>
#include "AuthService.hpp"
#include "src/jwt-cpp/include/jwt-cpp/jwt.h"

using namespace std;

const string _db_str = "database";
const string _username_str = "username";

AuthService::AuthService()
{
}

AuthService::~AuthService()
{
}

string AuthService::generate_token(string username, string database)
{
    auto c_username = username.c_str();
    auto c_database = database.c_str();
    auto token = jwt::create()
                     .set_issuer("auth0")
                     .set_type("JWS")
                     .set_payload_claim(_db_str, jwt::claim(string(c_database)))
                     .set_payload_claim(_username_str, jwt::claim(username))
                     //  .set_payload_claim(c_username, string("username"))
                     //  .set_payload_claim("database", string("database"))
                     .sign(jwt::algorithm::hs256{"supersecret"});
    return token;
}

AuthData AuthService::get_credentials(string token) {
    AuthData data;
    data.database_name= "database";
    cout << "IM HERE" << endl;
    auto decoded = jwt::decode(token);
    auto& database = decoded.get_payload_claim(_db_str);
    cout << database.as_string().c_str();
    data.database_name = database.as_string();
    cout << "DATABASE: " << data.database_name << endl;
    
    return data;

};

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