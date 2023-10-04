CXX:=clang++
CXXFLAGS:=-Wall -Wextra -pedantic -std=c++17
SRC_PATH:=./src
BIN_PATH:=./bin
TARGET:=$(BIN_PATH)/libgraphite.a
SRCS:=$(wildcard $(SRC_PATH)/*.cpp)
OBJS:=$(subst $(SRC_PATH),$(BIN_PATH),$(subst .cpp,.o,$(SRCS)))

$(TARGET): bin/ $(OBJS)
	ar rcs $(TARGET) $(OBJS)

bin/:
	mkdir -p $(BIN_PATH)

$(BIN_PATH)/%.o: $(SRC_PATH)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm $(BIN_PATH)/*
