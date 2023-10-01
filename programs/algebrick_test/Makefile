CXX=clang++
CXXFLAGS=-Wall -Wextra
LIB_PATH=../../lib
SRCS=$(wildcard src/*.cpp)
LIBS=$(wildcard $(LIB_PATH)/algebrick/*.cpp)

main: $(SRCS) $(LIB_PATH)
	mkdir -p bin
	$(CXX) $(CXXFLAGS) $(SRCS) $(LIBS) -o bin/algebrick_test
