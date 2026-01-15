########################
#    PROJECT CONFIG    #
########################
TARGET      = seed-finder
BUILD_DIR   = ./build
INC_DIR     = . ./include
SRC_DIR     = ./src
LIB_DIR     = ./libs

TARGET_PATH = $(BUILD_DIR)/$(TARGET)

#################
#    SOURCES    #
#################
PROJ_SRCS    = $(shell find $(SRC_DIR) -name '*.c')
PROJ_OBJS    = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(PROJ_SRCS))

#############
#    LIBS   #
#############
LIB_SRCS    = $(shell find $(LIB_DIR) -name '*.c')
LIB_OBJS    = $(patsubst $(LIB_DIR)/%.c, $(BUILD_DIR)/libs/%.o, $(LIB_SRCS))
ALL_OBJS    = $(PROJ_OBJS) $(LIB_OBJS)
DEP_FILES   = $(ALL_OBJS:.o=.d)

###########################
#    COMPILER SETTINGS    # 
###########################
CC          = gcc-15
STD         = -std=c2x
OPT         = -O3
W_FLAGS     = -Wall -Wextra -Wundef -Wshadow
DEP_FLAGS   = -MP -MD
#DEBUG_FLAGS := 

LIB_INC_DIRS = $(shell find $(LIB_DIR) -type d)
ALL_INC_DIRS = $(INC_DIR) $(LIB_INC_DIRS)

C_FLAGS     = $(STD) $(OPT) $(W_FLAGS) $(foreach D, $(ALL_INC_DIRS), -I$D) $(DEP_FLAGS) $(DEBUG_FLAGS)

#######################
#    BUILD TARGETS    #
#######################
all: $(TARGET_PATH)

$(TARGET_PATH): $(ALL_OBJS)
	@mkdir -p $(dir $@)
	$(CC) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(C_FLAGS) -c -o $@ $<

$(BUILD_DIR)/libs/%.o: $(LIB_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(C_FLAGS) -c -o $@ $<

run: $(TARGET_PATH)
	$(TARGET_PATH)

format:
	clang-format-22 -i $(PROJ_SRCS) $(shell find $(SRC_DIR) $(INC_DIR) -name '*.h')

clean:
	rm -rf $(BUILD_DIR)

-include $(DEP_FILES)

.PHONY: all clean format run
