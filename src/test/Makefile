CXX=clang++
CXXFLAGS=-Wall -Wextra
LIB_PATH=../../lib
SRCS=$(wildcard *.cpp)
LIBS=$(wildcard $(LIB_PATH)/algebrick/*.cpp)

main: $(SRCS) $(LIB_PATH)
	$(CXX) $(CXXFLAGS) $(SRCS) $(LIBS) -o main
