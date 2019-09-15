FROM grpc/cxx
RUN mkdir bridgedb
WORKDIR /bridgedb
ADD . .
WORKDIR /bridgedb/src/network
# WORKDIR /bridgedb/src/network
RUN ./proto.sh
WORKDIR /bridgedb
# RUN g++ network.cpp -o network.out -std=c++11
# RUN g++ network.cpp -o network.out -L/usr/local/lib -L/usr/local/lib -lprotobuf -pthread -lpthread -lgrpc++
RUN make networking
RUN ls -l
CMD [ "./test" ]