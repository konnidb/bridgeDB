FROM grpc/cxx AS builder
RUN mkdir bridgedb
WORKDIR /bridgedb
ADD . .
WORKDIR /bridgedb/src/network
RUN make
WORKDIR /bridgedb
CMD [ "./test" ]