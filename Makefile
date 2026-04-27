CC = gcc
CFLAGS = -Iinclude -Wall -Wextra

SRCS = src/main.c src/scanner.c src/ast.c src/parser.c src/codegen.c
OBJS = $(SRCS:.c=.o)
TARGET = minicc

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

clean:
	rm -f src/*.o $(TARGET)