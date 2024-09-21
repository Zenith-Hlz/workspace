CC = g++
CFLAGS = -Wall -std=c++11

SRCS = main.cpp book.cpp library.cpp
OBJS = $(SRCS:.cpp=.o)
HEADERS = book.h library.h

TARGET = main

$(TARGET):$(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o:%.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJS) $(TARGET)