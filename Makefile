CC = gcc
CFLAGS = 
SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))
TARGET_DIR = bin
TARGET = $(TARGET_DIR)/main

all: $(TARGET)

$(TARGET): $(OBJ)
	mkdir -p $(TARGET_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(TARGET)