CC=gcc
SRC_DIR=./src
BIN_DIR=./bin
OBJ_DIR=./obj
INCLUDE_DIRS=-I$(SRC_DIR)
BIN=gpgpusim_install
SRCS=$(wildcard $(SRC_DIR)/*.c)
OBJS=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

all: $(OBJS)
	$(CC) $(INCLUDE_DIRS) $^ -o $(BIN)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(INCLUDE_DIRS) -c $^ -o $@

clean:
	@rm bin/*
	@rm obj/*
