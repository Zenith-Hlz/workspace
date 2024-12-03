CC = g++
CFLAGS = -Wall -std=c++11

SRCS = main.cpp hashtable.cpp
OBJS = $(SRCS:.cpp=.o)
HEADERS = hashtable.h

TARGET = main

$(TARGET):$(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o:%.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJS) $(TARGET)