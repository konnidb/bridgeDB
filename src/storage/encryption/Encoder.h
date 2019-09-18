#pragma once
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class Encoder
{
private:
    fstream* in_stream;

public:
    Encoder(fstream* in_stream);
    fstream* enconde(void);
    static void encode_stream(fstream* stream, string stream_name);
    static void encode_stream(fstream* stream);
    static string encode_message(char*);
    static char encode_character();
    static string encode_message(string);
    ~Encoder();
};
