#include "Encoder.cc"
#include "Decoder.cc"
using namespace std;

int main(int argc, char const *argv[])
{
    fstream stream;
    stream.open("tmp.file",  ios::out);
    stream.write("Esta es una prueba",sizeof("Esta es una prueba"));
    Encoder::encode_stream(&stream);
    stream.close();
    return 0;
}
