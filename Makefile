CC = g++
CFLAGS = -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++20
RM = rm

SHARED_DIR =./shared
CLIENT_SRC = ./src/client
CLIENT_BUILD = ./src/client/build
SERVER_SRC = ./src/server
SERVER_BUILD = ./src/server/build
DEBUG_DIR = ./debug

CLIENT_TARGETS = $(CLIENT_BUILD)/map.o $(CLIENT_BUILD)/tile.o $(CLIENT_BUILD)/player.o
SERVER_TARGETS = 

EXAMPLE_DIR = ./docs/inspiration

all: client server

client: map.o tile.o player.o
	$(CC) $(CFLAGS) -o ${DEBUG_DIR}/client ${CLIENT_SRC}/client.cpp $(CLIENT_TARGETS)

server: $(SERVER_TARGETS)
	$(CC) $(CFLAGS) -o ${DEBUG_DIR}/server ${SERVER_SRC}/server.cpp $(SERVER_TARGETS)

map.o:
	$(CC) $(CFLAGS) -o ${CLIENT_BUILD}/map.o -c ${CLIENT_SRC}/include/map.cpp 

tile.o:
	$(CC) $(CFLAGS) -o $(CLIENT_BUILD)/tile.o -c $(CLIENT_SRC)/include/tile.cpp

player.o:
	$(CC) $(CFLAGS) -o $(CLIENT_BUILD)/player.o -c $(CLIENT_SRC)/include/player.cpp

clean:
	$(RM) $(CLIENT_TARGETS) $(SERVER_TARGETS)
	$(RM) $(DEBUG_DIR)/client $(DEBUG_DIR)/server

# EXAMPLE TARGETS... WILL BE LEAVING SOON
examples: exampleMMOClient exampleIsoClient exampleServer

cleanExamples:
	$(RM) $(EXAMPLE_DIR)/mmoEXClient ${EXAMPLE_DIR}/server ${EXAMPLE_DIR}/isoEXClient

exampleMMOClient:
	$(CC) $(CFLAGS) -o ${EXAMPLE_DIR}/mmoEXClient ${EXAMPLE_DIR}/MMO_client_example.cpp 

exampleIsoClient:
	$(CC) $(CFLAGS) -o ${EXAMPLE_DIR}/isoEXClient ${EXAMPLE_DIR}/isometric_example.cpp 

exampleServer:
	$(CC) $(CFLAGS) -o ${EXAMPLE_DIR}/server ${EXAMPLE_DIR}/server.cpp