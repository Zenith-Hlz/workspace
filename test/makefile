CC = g++
CFLAGS = -Wall -std=c++11

SRCS = test.cpp
OBJS = $(SRCS:.cpp=.o)
HEADERS = 

TARGET = test

$(TARGET):$(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o:%.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJS) $(TARGET)