TARGET_EXEC ?= server

BUILD_DIR ?= ./build
SRC_DIRS ?= ./

SRCS := $(shell find $(SRC_DIRS)  -name *.c -or -name *.cpp)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))
LDFLAGS :=  
CFLAGS ?= $(INC_FLAGS) -MMD -MP -std=gnu11 -g
CPPFLAGS ?= $(INC_FLAGS) -MMD -MP -std=c++14 -g
CC = gcc
CXX = g++
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# c source
$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) $(CFLAGS) -c $< -o $@

# cpp source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) -c $< -o $@

.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p