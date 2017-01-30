CFLAGS:=-c -Wall -Weffc++ -Werror -g -std=c++11 -I ./include -isystem /usr/include
LDFLAGS:=-lboost_system -lboost_locale -lboost_thread

all: Client
	g++ -L/usr/lib -o bin/Client bin/ConnectionHandler.o bin/KeyBoardProtocol.o bin/MainClient.o bin/MessageEncDec.o bin/Packet.o bin/SocketProtocol.o $(LDFLAGS)

Client: bin/ConnectionHandler.o bin/KeyBoardProtocol.o bin/MainClient.o bin/MessageEncDec.o bin/Packet.o bin/SocketProtocol.o
	
bin/ConnectionHandler.o: src/ConnectionHandler.cpp
	g++ $(CFLAGS) -o bin/ConnectionHandler.o src/ConnectionHandler.cpp

bin/KeyBoardProtocol.o: src/KeyBoardProtocol.cpp
	g++ $(CFLAGS) -o bin/KeyBoardProtocol.o src/KeyBoardProtocol.cpp

bin/MainClient.o: src/MainClient.cpp
	g++ $(CFLAGS) -o bin/MainClient.o src/MainClient.cpp

bin/MessageEncDec.o: src/MessageEncDec.cpp
	g++ $(CFLAGS) -o bin/MessageEncDec.o src/MessageEncDec.cpp

bin/Packet.o: src/Packet.cpp
	g++ $(CFLAGS) -o bin/Packet.o src/Packet.cpp

bin/SocketProtocol.o: src/SocketProtocol.cpp
	g++ $(CFLAGS) -o bin/SocketProtocol.o src/SocketProtocol.cpp
	
.PHONY: clean
clean:
	rm -f bin/*
