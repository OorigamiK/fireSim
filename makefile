# Compilers
CXX = g++
CC = gcc

# Compiler flags
CXXFLAGS = -Iinclude -std=c++17 -Wall -Wextra
CFLAGS = -Iinclude -Wall -Wextra

# Linker flags for OpenGL + GLFW (Linux)
LDFLAGS = -lglfw -lGL -ldl -lm -lX11 -lpthread -lXrandr -lXi

# Sources
SRC_CPP = main.cpp physics.cpp
SRC_C = glad.c

# Build directory
BUILD_DIR = build

# Object files mapped to build directory
OBJ_CPP = $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRC_CPP))
OBJ_C = $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRC_C))
OBJ = $(OBJ_CPP) $(OBJ_C)

# Output binary
TARGET = fireSim

# Default target
all: $(TARGET)

# Link final binary
$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Compile C++ source files into build/
$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile C source files into build/
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create build directory if not exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean all generated files
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean

PHONY: run
run:
	./fireSim
