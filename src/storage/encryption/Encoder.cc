#include <string>
#include <iostream>
#include <fstream>
#include "Encoder.h"
using namespace std;

Encoder::Encoder(fstream *in_stream)
{
    this->in_stream = in_stream;
}

void Encoder::encode_stream(fstream* stream)
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

void Encoder::encode_stream(fstream* stream, string stream_name)
{
    stream->open(stream_name);
    Encoder::encode_stream(stream);
}

fstream* Encoder::enconde(void)
{
    return this->in_stream;
}

Encoder::~Encoder()
{
    delete this->in_stream;
}
