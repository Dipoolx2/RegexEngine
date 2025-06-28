# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17

# Target executable
TARGET := engine_tester

# Source files
SRCS := PrinterVisitor.cpp engine_tester.cpp Regex.cpp

# Default target
all: build run

# Build the executable
build: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $(SRCS)

# Run the executable
run:
	./$(TARGET)

# Clean up
clean:
	rm -f $(TARGET)

.PHONY: all build clean
