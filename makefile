# Makefile for building Ferns Farm game
# Usage:
#   make           -> compile game into build/
#   make clean     -> remove build and out directories
#   make package   -> zip sources into out/
#   make list      -> list package contents

# C++ compiler to use
CXX = g++
# Compiler flags: C++11, show all warnings
CXXFLAGS = -std=c++11 -Wall

# Directory for zipped output
OUT_DIR = out
# Directory for build artifacts
BUILD_DIR = build
# List of source files
SRCS = main.cpp Player.cpp Crop.cpp Event.cpp EventManager.cpp Tool.cpp
# Corresponding object files in build dir
OBJS = $(SRCS:%.cpp=$(BUILD_DIR)/%.o)
# Name of the executable
TARGET = harvest_days

# Phony targets: not actual files
.PHONY: all clean package list

# Default: build the executable
all: $(BUILD_DIR)/$(TARGET)

# Ensure build dir exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Link step: create the executable
$(BUILD_DIR)/$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files
$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean: remove build and out dirs
clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(OUT_DIR)

# Package sources and headers into zip
package: all
	mkdir -p $(OUT_DIR)
	zip -j $(OUT_DIR)/harvest_submission.zip $(SRCS) *.h

# List the contents of the zip package
list: package
	unzip -l $(OUT_DIR)/harvest_submission.zip
