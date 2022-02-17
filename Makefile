CC=g++
CPPFLAGS=-std=c++20 -lglut -lGL -g
OPENGL = `pkg-config opengl --cflags --libs`
LIBS = $(OPENGL)

pong: src/pong.cpp src/engine.cpp src/object.cpp src/paddle.cpp
	$(CC) -o pong src/pong.cpp src/engine.cpp src/object.cpp src/paddle.cpp $(CPPFLAGS)

clean:
	$(RM) pong