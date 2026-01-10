CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra
INCLUDES := -Iinclude

SRC_DIR := src
BUILD_DIR := build

# Find all .cpp files recursively
SRC_FILES := $(shell find $(SRC_DIR) -name '*.cpp')

# Map src/.../*.cpp → build/.../*.o
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))

TARGET := laddle

all: $(TARGET)

# Link
$(TARGET): $(OBJ_FILES)
	$(CXX) $(OBJ_FILES) -o $@  -lsfml-graphics -lsfml-window -lsfml-system

# Compile
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

run: all
	./$(TARGET)

.PHONY: all clean run