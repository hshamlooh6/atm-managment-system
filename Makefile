CC = cc
CFLAGS = -Wall -Wextra -std=gnu11 -g

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
LDFLAGS =
else
LDFLAGS = -lcrypt
endif

SRC_DIR = src
OBJ_DIR = build

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))
HEADERS = $(SRC_DIR)/header.h

TARGET = atm

.PHONY: all run test clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

run: $(TARGET)
	./$(TARGET)

test: tests/test_interest.c $(SRC_DIR)/interest.c $(HEADERS)
	$(CC) $(CFLAGS) tests/test_interest.c $(SRC_DIR)/interest.c -o build/test_interest
	./build/test_interest

clean:
	rm -rf $(OBJ_DIR) $(TARGET)
