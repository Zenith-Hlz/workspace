CC := g++
override CFLAGS += -std=c++11
TARGET := main

# $(wildcard *.cpp /xxx/xxx/*.cpp): get all .cpp files from the current directory and dir "/xxx/xxx/"
SRCS := $(wildcard *.cpp)
# $(patsubst %.cpp,%.o,$(SRCS)): substitute all ".cpp" file name strings to ".o" file name strings
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

test1:
	@make main CFLAGS="-D _test_1_"
test2:
	@make main CFLAGS="-D _test_2_"
test3:
	@make main CFLAGS="-D _test_3_"

$(TARGET): $(OBJS)
	$(CC) -o $@ $^
%.o: %.cpp
	$(CC) $(CFLAGS) -c $<
clean:
	rm -rf $(TARGET) *.o

.PHONY: clean test1 test2 test3