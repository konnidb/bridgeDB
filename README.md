# BridgeDB

BridgeDB is an opensource Graph based database with a NoSQL approach.
It's name comes from the Bridge problem of Königsberg, a famous problem which solution uses Graph theory. The motivation behind BridgeDB was an school project where we needed to find a way to store data using simple binary files and then load them in memory in a structure where we could do graph operations such as pattern recognition, shortest paths, MSTs, etc. After spending a few months thinking about creating a language similar to Cypher from Neo4j we decided to move on creating an RPC server where we could easely call our methods using HTTP 2.

Feel free to look at the code, critique, and give feedback based on knowledge and experience.

### Note
This project is in a very early stage of development and our goal here is to implement a file system optimized to do graph operations when information is loaded on memory. Our system sill has a lot of pitfalls and our projection is to fix them in a short to medium period of time.

Also as part of being an school project, our main goal is to make this work in an stable way and make it available to everyone disposed to use our.

### Dependencies
- GRPC
- Protocol Buffers 3.8+
- Make
- Gcc compiler compatible with C++ 17
- Git
- Download git submodules of this project.

### Build the project
``` shell
make clean
make
./src/network/build/server.out
```


### Creating a database

In BridgeDB we have three concepts needed to operate on the database.
- Token
- Database
- Graph

Every time you create an instance of BridgeDB you need to create a token using the RPC method called `CreateSession`. This method generates a token using a SHA256 algorithm. After the database will be configured and you can start to perform operations, operations defined in the `src/network/network.proto` file.

Once you have created your session in the previous step your token will containt certain information about the Database name that you will be performing operations and also the Graph were the information will be stored.

Similar to the concept of documents in NoSQL databases such as MongoDB we manage the conept of Graphs, one graph is independant of another, but a database could have multple graphs inside. Which graph will you be working with will depend on the authentication data used to create your token.

Is important to note before you start creating relations between multiple vertex that we have a difference between a Node and a Vertex.

A Node is the unit of information, is where data is truly stored, your nodes contain the information you actually want to be stored while a Vertex is a wrapper for a Node and the Edges it could have.

<strong>Important:</strong> we originally planed this to work only with directed Graphs, so if you plan to configure the databases using a Non-direceted edges, what our engine actually does is create another Edge that goes from the Destination Node to the Origin Node with the exact same properties as the original.