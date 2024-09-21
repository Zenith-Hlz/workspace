CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -pedantic

TARGET := main
OBJS := main.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)

.PHONY: all clean
