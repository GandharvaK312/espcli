CC = gcc

CFLAGS = -Wall -Wextra -Wpedantic -std=c11
CPPFLAGS = -Iinclude

TARGET = build/espcli

SRC = $(wildcard src/*.c) \
      $(wildcard src/gpio/*.c)

OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	mkdir -p $(dir $@)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

build/%.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build

.PHONY: all clean
