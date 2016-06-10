FS_DIR = $(shell pwd)
SRC_DIR = $(FS_DIR)/src
BUILD_DIR = $(FS_DIR)/build
BIN_DIR = $(FS_DIR)/bin
INCLUDE_DIR = $(FS_DIR)/include

CFLAGS = -g -Wall -Werror -Wextra -ansi -pedantic-errors -lreadline -I$(INCLUDE_DIR)

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(addprefix $(BUILD_DIR)/, $(notdir $(SRC_FILES:.c=.o)))

file_system: $(OBJ_FILES)
	gcc $(CFLAGS) $(BUILD_DIR)/*.o -o $(BIN_DIR)/file_system

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE_DIR)/file_system.h
	gcc $(CFLAGS) -c $< -o $@

run:
	$(BIN_DIR)/file_system 

.PHONY: clean
clean: 
	rm -f $(BUILD_DIR)/*.o $(BIN_DIR)/file_system
