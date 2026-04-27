CC = gcc
CFLAGS = -Iinclude -Wall -Wextra

SRCS = src/main.c src/scanner.c
OBJS = $(SRCS:.c=.o)
TARGET = minicc

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

clean:
	rm -f src/*.o $(TARGET)