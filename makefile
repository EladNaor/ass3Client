PROGRAM = TFTPclient

SRCS = 	ConnectionHandler.cpp \
		KeyBoardProtocol.cpp \
		MainClient.cpp \
		MessageEncDec.cpp \
		Packet.cpp \
		SocketProtocol.cpp

SRCDIR = src
BINDIR = bin

OBJS = $(SRCS:%.cpp=$(BINDIR)/%.o)

CC = g++

CFLAGS = -g -std=c++11 -Wall -Weffc++ -Werror
LFLAGS = -L/usr/lib

INCLUDES = -I./include -I./include/Packet -isystem /usr/include
LIBS = -lboost_locale -lboost_system -lboost_thread

.PHONY: all
all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CC) $(LFLAGS) -o $(BINDIR)/$(PROGRAM) $+ $(LIBS)

$(BINDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) -c $(CFLAGS) $(INCLUDES) -o $@ $<

.PHONY: clean
clean:
	rm -rf $(BINDIR)/*
