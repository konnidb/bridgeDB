#!/bin/bash
protoc --grpc_out=. --plugin=protoc-gen-grpc=/usr/local/bin/grpc_cpp_plugin --cpp_out=. network.proto
