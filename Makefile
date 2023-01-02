CC=g++
CPPFLAGS=-std=c++20 -lglut -lGL -g
OPENGL = `pkg-config opengl --cflags --libs`
EIGEN3_INCLUDE_DIR = /usr/include/eigen3
LIBS = $(OPENGL)
SRC_DIR := ./src
OBJ_DIR := ./obj
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

TARGET := pong

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) -w -I $(EIGEN3_INCLUDE_DIR) -o $@ $^ $(CPPFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -I $(EIGEN3_INCLUDE_DIR) $(CPPFLAGS) -c $< -o $@

test: src/geometry.cpp
	$(CC) -w -I $(EIGEN3_INCLUDE_DIR) -o tests test/test_geometry.cpp src/geometry.cpp /usr/lib/libgtest.a /usr/lib/libgtest_main.a -lpthread $(CPPFLAGS)

clean:
	$(RM) pong