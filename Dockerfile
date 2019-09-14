FROM grpc/cxx
RUN mkdir bridgedb
WORKDIR /bridgedb
ADD . .
WORKDIR /bridgedb/src/network
RUN ./proto.sh
WORKDIR /bridgedb
RUN g++ -Wall network.cpp -o network.out