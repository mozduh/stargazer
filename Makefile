CC = g++
CFLAGS = -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++20

SHARED_DIR =./shared
CLIENT_SRC=./src/client
CLIENT_BUILD=./src/client/build
SERVER_SRC=./src/server
SERVER_BUILD=./src/server/build
DEBUG_DIR=./debug

CLIENT_TARGETS = client.o map.o olcPixelGameEngine.o
SERVER_TARGETS = server.o olcPGEX_Network.o

all: client server

client: ${CLIENT_BUILD}/map.o $(CLIENT_BUILD)/tile.o
	$(CC) $(CFLAGS) -o ${DEBUG_DIR}/client ${CLIENT_SRC}/client.cpp $(CLIENT_BUILD)/map.o $(CLIENT_BUILD)/tile.o

server:
	$(CC) $(CFLAGS) -o ${DEBUG_DIR}/server ${SERVER_SRC}/server.cpp

$(CLIENT_BUILD)/map.o: 
	$(CC) $(CFLAGS) -o ${CLIENT_BUILD}/map.o -c ${CLIENT_SRC}/include/map.cpp 

$(CLIENT_BUILD)/tile.o:
	$(CC) $(CFLAGS) -o $(CLIENT_BUILD)/tile.o -c $(CLIENT_SRC)/include/tile.cpp

# EXAMPLE TARGETS... WILL BE LEAVING SOON
examples: exampleMMOClient exampleIsoClient

exampleMMOClient:
	$(CC) $(CFLAGS) -o ${DEBUG_DIR}/mmoEXClient ${CLIENT_SRC}/MMO_client_example.cpp 

exampleIsoClient:
	$(CC) $(CFLAGS) -o ${DEBUG_DIR}/isoEXClient ${CLIENT_SRC}/isometric_example.cpp 
