CXX := g++

CXXFLAGS := -Wall -Wextra -std=c++11

SRCS := main.cpp product.cpp sum.cpp

OBJS := $(SRCS:.cpp=.o)

all: main

debug: CXXFLAGS += -g -DDEBUG
debug: main

main: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o main

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f main $(OBJS)