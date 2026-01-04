########################
#    PROJECT CONFIG    #
########################
TARGET 	    = seed_finder
BUILD_DIR   = ./build
INC_DIR 	= ./include
SRC_DIR		= ./src

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
CC          = gcc-13
STD         = -std=c2x
OPT         = -O3
W_FLAGS     = -Wall -Wextra -Wundef -Wshadow
DEP_FLAGS   = -MP -MD
C_FLAGS     = $(STD) $(OPT) $(W_FLAGS) -I$(INC_DIR) $(DEP_FLAGS)

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

format:
	clang-format.exe -i $(C_FILES) $(H_FILES)

clean:
	rm -rf $(BUILD_DIR)

-include $(DEP_FILES)

.PHONY: all clean format
