#pragma once
#include <iostream>
#include <fstream>
using namespace std;

class Enconder
{
private:
    fstream* in_stream;

public:
    Enconder(fstream* in_stream);
    fstream* enconde(void);
    static void enconde_stream(fstream* stream);
    static string encode_message(char*);
    static char encode_character();
    static string encode_message(string);
    ~Enconder();
};

Enconder::Enconder(fstream *in_stream)
{
    this->in_stream = in_stream;
}

void Enconder::enconde_stream(fstream* stream)
{
    char ch;
    fstream tmp_stream;
    tmp_stream.open("tmpfile.txt");
    while (stream->eof() == 0)
    {
        *stream>>ch;
        ch=ch+100;
        tmp_stream<<ch;
    }

    tmp_stream.close();
}

fstream* Enconder::enconde(void)
{
    return this->in_stream;
}

Enconder::~Enconder()
{
    delete this->in_stream;
}
