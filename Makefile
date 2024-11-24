# Compiler and linker
CXX = g++
GTEST_DIR = /opt/homebrew/Cellar/googletest/1.15.2
NLOHMANN_JSON_INC = /opt/homebrew/Cellar/nlohmann-json/3.11.3/include

CXXFLAGS = -std=c++17 -Wall -I./include -I$(GTEST_DIR)/include -I$(NLOHMANN_JSON_INC)
LDFLAGS = -L$(GTEST_DIR)/lib -lgtest -lgtest_main -pthread

# Directories
SRCDIR = src
TESTDIR = tests
BUILDDIR = build
INCLUDEDIR = include

# Source files for the app and tests
APP_SOURCES = $(SRCDIR)/main.cpp $(SRCDIR)/robot.cpp
TEST_SOURCES = $(SRCDIR)/robot.cpp $(TESTDIR)/tests.cpp

# Object files for the app and tests
APP_OBJECTS = $(APP_SOURCES:%.cpp=$(BUILDDIR)/%.o)
TEST_OBJECTS = $(TEST_SOURCES:%.cpp=$(BUILDDIR)/%.o)

# Executables for the app and tests
APP_EXEC = robot
TEST_EXEC = robot_tests

# Default target (build both app and tests)
all: $(APP_EXEC) $(TEST_EXEC)

# Target to build the application
$(APP_EXEC): $(APP_OBJECTS)
	$(CXX) $(APP_OBJECTS) -o $(APP_EXEC)

# Target to build the test executable
$(TEST_EXEC): $(TEST_OBJECTS)
	$(CXX) $(TEST_OBJECTS) -o $(TEST_EXEC) $(LDFLAGS)

# Rule for compiling application source files into object files
$(BUILDDIR)/$(SRCDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)/$(SRCDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule for compiling test source files into object files
$(BUILDDIR)/$(TESTDIR)/%.o: $(TESTDIR)/%.cpp
	@mkdir -p $(BUILDDIR)/$(TESTDIR)
	$(CXX) $(CXXFLAGS) -Wno-integer-overflow -c $< -o $@

# Target to run the tests
test: $(TEST_EXEC)
	./$(TEST_EXEC)

# Clean up object files and executables
clean:
	rm -f $(BUILDDIR)/$(SRCDIR)/*.o $(BUILDDIR)/$(TESTDIR)/*.o $(APP_EXEC) $(TEST_EXEC)

.PHONY: all clean test
