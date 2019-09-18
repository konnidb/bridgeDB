#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Decoder
{
private:
    fstream* stream;
public:
    Decoder(fstream* stream);
    fstream* decode();
    static void decode_stream(fstream* stream, string stream_name);
    static void decode_stream(fstream* stream);
    ~Decoder();
};

Decoder::Decoder(fstream* stream)
{
}

void Decoder::decode_stream(fstream* stream, string stream_name)
{
    stream->open(stream_name);
    Decoder::decode_stream(stream);
}

void Decoder::decode_stream(fstream* stream)
{
    fstream tmp_stream;
    char ch;
    while (stream->eof() == 0)
    {
        *stream>>ch;
        ch=ch-100;
        tmp_stream<<ch;
    }
    stream->close();
    stream = &tmp_stream;
}

Decoder::~Decoder()
{
}
