########################
#    PROJECT CONFIG    #
########################
TARGET 	    = seed_finder
INC 		= ./include
SRC			= ./src
DIRS 		= . locale rng engine

SRC_DIR     = $(foreach D, $(DIRS), $(wildcard $(SRC)/$(D)))
INC_DIR     = $(foreach D, $(DIRS), $(wildcard $(INC)/$(D)))

$(info $(SRC_DIR))
$(info $(INC_DIR))

BUILD_DIR   = ./build

#INC_DIR     = ./include ./include
#SRC_DIR 	= ./src ./src/locale ./src/engine ./src/rng

###############
#    FILES    #
###############
C_FILES     = $(foreach D, $(SRC_DIR), $(wildcard $(D)/*.c))
H_FILES     = $(foreach D, $(INC_DIR), $(wildcard $(D)/*.h))
OBJ_FILES   = $(patsubst %.c, %.o, $(C_FILES))
DEP_FILES   = $(patsubst %.c, %.d, $(C_FILES))

###########################
#    COMPILER SETTINGS    # 
###########################
CC          = gcc
STD         = -std=c23
OPT         = -O3
W_FLAGS     = -Wall -Wextra -Wundef -Wshadow
DEP_FLAGS   = -MP -MD
C_FLAGS     = $(STD) $(OPT) $(W_FLAGS) -I$(INC) $(DEP_FLAGS)

#######################
#    BUILD TARGETS    #
#######################

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(C_FLAGS) -c -o $@ $<

format:
	clang-format -i $(C_FILES) $(H_FILES)

clean:
	rm -rf $(BINARY) $(OBJ_FILES) $(DEP_FILES)

-include $(DEP_FILES)

.PHONY: all clean format
