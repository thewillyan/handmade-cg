LIBS:=algebrick graphite
LIBS_PATH:=$(shell realpath ../../lib)
LIB_FLAGS:=$(foreach lib,$(LIBS),\
		   -I $(LIBS_PATH)/$(lib)/include -L $(LIBS_PATH)/$(lib)/bin -l $(lib)) \
		   -l SDL2
LIB_FILES:=$(foreach lib,$(LIBS),$(LIBS_PATH)/$(lib)/bin/lib$(lib).a)
CXX:=clang++
CXXFLAGS:=-Wall -Wextra -pedantic -std=c++17
SRC_PATH:=./src
BIN_PATH:=./bin
TARGET:=$(BIN_PATH)/graphite_test
SRCS:=$(wildcard $(SRC_PATH)/*.cpp)
OBJS:=$(subst $(SRC_PATH),$(BIN_PATH),$(subst .cpp,.o,$(SRCS)))

$(TARGET): bin/ $(LIB_FILES) $(OBJS)
	$(CXX) $(OBJS) $(LIB_FLAGS) -o $(TARGET)

bin/:
	mkdir -p $(BIN_PATH)

$(BIN_PATH)/%.o: $(SRC_PATH)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.a:
	$(MAKE) -C $(@D)/..

run:
	$(TARGET)

clean:
	rm $(BIN_PATH)/*
