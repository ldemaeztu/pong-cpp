CC=g++
CPPFLAGS=-std=c++20 -lglut -lGL -g
OPENGL = `pkg-config opengl --cflags --libs`
EIGEN3_INCLUDE_DIR = /usr/include/eigen3
LIBS = $(OPENGL)

pong: src/pong.cpp src/engine.cpp src/object.cpp src/paddle.cpp src/ball.cpp src/kalman.cpp src/balltracker.cpp src/geometry.cpp src/configloader.cpp
	$(CC) -w -I $(EIGEN3_INCLUDE_DIR) -o pong src/pong.cpp src/engine.cpp src/object.cpp src/paddle.cpp src/ball.cpp src/kalman.cpp src/balltracker.cpp src/geometry.cpp src/configloader.cpp $(CPPFLAGS)

test: src/geometry.cpp
	$(CC) -w -I $(EIGEN3_INCLUDE_DIR) -o tests test/test_geometry.cpp src/geometry.cpp /usr/lib/libgtest.a /usr/lib/libgtest_main.a -lpthread $(CPPFLAGS)

clean:
	$(RM) pong