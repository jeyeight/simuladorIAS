CC = gcc
CFLAGS = -Wall -Wextra 
SRC = main.c utils.c memoria.c fila.c processador.c barramento.c flags.c uc.c
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
TARGET_DIR = bin
TARGET = $(TARGET_DIR)/main

all: $(TARGET)

$(TARGET): $(OBJ)
	mkdir -p $(TARGET_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(TARGET)
