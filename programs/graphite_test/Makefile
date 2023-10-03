CXX=clang++
CXXFLAGS=-Wall -Wextra -lSDL2 -std=c++17
LIB_PATH=../../lib
SRCS=$(wildcard src/*.cpp)
LIBS=$(wildcard $(LIB_PATH)/algebrick/*.cpp $(LIB_PATH)/graphite/*.cpp)

main: $(SRCS) $(LIBS)
	mkdir -p bin
	$(CXX) $(CXXFLAGS) $(SRCS) $(LIBS) -o bin/graphite_test
