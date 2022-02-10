CC=g++
CFLAGS=-std=c++20 -lglut -lGL -g
OPENGL = `pkg-config opengl --cflags --libs`
LIBS = $(OPENGL)

pong: src/pong.cpp src/application.cpp
	$(CC) -o pong src/pong.cpp src/application.cpp $(CFLAGS)