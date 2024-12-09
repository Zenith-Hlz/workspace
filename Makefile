CC = g++
CFLAGS = -Wall -std=c++11

SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)
HEADERS = 

TARGET = main

$(TARGET):$(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o:%.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJS) $(TARGET) gen test