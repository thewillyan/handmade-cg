CXX=clang++
CXXFLAGS=-Wall -Wextra -lSDL2
LIB_PATH=../../lib
SRCS=$(wildcard src/*.cpp)
LIBS=$(wildcard $(LIB_PATH)/graphite/*.cpp)

main: $(SRCS) $(LIB_PATH)
	mkdir -p bin
	$(CXX) $(CXXFLAGS) $(SRCS) $(LIBS) -o bin/graphite_test
