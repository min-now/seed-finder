########################
#    PROJECT CONFIG    #
########################
TARGET 	    = seed_finder
BUILD_DIR   = ./build
INC_DIR 	= ./include .
SRC_DIR		= ./src
LIB_DIR		= ./lib

TARGET_PATH = $(BUILD_DIR)/$(TARGET)

#################
#    SOURCES    #
#################
C_FILES     = $(shell find $(SRC_DIR) -name '*.c')
H_FILES     = $(shell find $(SRC_DIR) $(INC_DIR) -name '*.h')

OBJ_FILES   = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(C_FILES))
DEP_FILES   = $(OBJ_FILES:.o=.d)

###########################
#    COMPILER SETTINGS    # 
###########################
CC          = clang-19
STD         = -std=c23
OPT         = -O3
W_FLAGS     = -Wall -Wextra -Wundef -Wshadow
DEP_FLAGS   = -MP -MD
C_FLAGS     = $(STD) $(OPT) $(W_FLAGS) $(foreach D, $(INC_DIR), -I$D) $(DEP_FLAGS)

###################
#    LIBRARIES    #
###################
LIB_SHA1		= libsha1.a
LIB_SHA1_DIR 	= $(LIB_DIR)/libsha1

LIB_SHA1_C_FILES = $(wildcard $(LIB_SHA1_DIR)/*.c)
LIB_SHA1_OBJ_FILES = $(LIB_SHA1_C_FILES:.c=.o)

#######################
#    BUILD TARGETS    #
#######################

all: $(TARGET_PATH)

$(TARGET_PATH): $(OBJ_FILES)
	@mkdir -p $(dir $@)
	$(CC) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(C_FLAGS) -c -o $@ $<

run: $(TARGET_PATH)
	$(TARGET_PATH)

format:
	clang-format.exe -i $(C_FILES) $(H_FILES)

clean:
	rm -rf $(BUILD_DIR)

-include $(DEP_FILES)

.PHONY: all clean format run
