FROM gcc
RUN apt-get install -y lex bison

RUN mkdir -p bridgedb
COPY . /bridgedb
