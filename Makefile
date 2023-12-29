
CLIENT_SRC=./src/client
CLIENT_BUILD=./src/client/build
SERVER_SRC=./src/server
DEBUG_DIR=./debug

main: client server

examples: exampleMMOClient exampleIsoClient

client: map
	g++ -o ${DEBUG_DIR}/sg_client ${CLIENT_SRC}/client.cpp $(CLIENT_BUILD)/map.o -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++20

server:
	g++ -o ${DEBUG_DIR}/sg_server ${SERVER_SRC}/server.cpp -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++20

map: 
	g++ -o ${CLIENT_BUILD}/map.o -c ${CLIENT_SRC}/include/map.cpp -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++20

exampleMMOClient:
	g++ -o ${DEBUG_DIR}/mmoEXClient ${CLIENT_SRC}/MMO_client_example.cpp -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++20

exampleIsoClient:
	g++ -o ${DEBUG_DIR}/isoEXClient ${CLIENT_SRC}/isometric_example.cpp -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++20
