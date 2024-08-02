# The compiler to use
COMPILER = clang++

# Compiler flags
FLAGS = -std=c++14

SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
BIN_DIR = bin

BINOMIAL_DIR = $(SRC_DIR)/binomial
FINITE_DIFF_DIR = $(SRC_DIR)/finite_difference
MONTE_CARLO_DIR = $(SRC_DIR)/monte_carlo
GAUSSIAN_DIR = $(SRC_DIR)/gaussian
OPTION_DIR = $(SRC_DIR)/option
UTILS_DIR = $(SRC_DIR)/utils

TARGETS = $(BIN_DIR)/finite_difference.out $(BIN_DIR)/monte_carlo.out $(BIN_DIR)/binomial.out
# List of source files
FINITE_DIFF_SRCS = $(SRC_DIR)/finite_difference_main.cpp $(wildcard $(FINITE_DIFF_DIR)/*.cpp $(OPTION_DIR)/*.cpp $(UTILS_DIR)/*.cpp)

FINITE_DIFF_OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(FINITE_DIFF_SRCS))

MONTE_CARLO_SRCS = $(SRC_DIR)/monte_carlo_main.cpp $(wildcard $(MONTE_CARLO_DIR)/*.cpp $(GAUSSIAN_DIR)/*.cpp $(OPTION_DIR)/*.cpp $(UTILS_DIR)/*.cpp)

MONTE_CARLO_OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(MONTE_CARLO_SRCS))

BINOMIAL_SRCS = $(SRC_DIR)/binomial_main.cpp $(wildcard $(BINOMIAL_DIR)/*.cpp $(OPTION_DIR)/*.cpp $(UTILS_DIR)/*.cpp)

BINOMIAL_OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(BINOMIAL_SRCS))

# Default target
all: $(TARGETS)

# Rule to link the object files to create the executable
$(BIN_DIR)/finite_difference.out: $(FINITE_DIFF_OBJS)
	@mkdir -p $(BIN_DIR)
	$(COMPILER) $(FLAGS) $^ -o $@

$(BIN_DIR)/monte_carlo.out: $(MONTE_CARLO_OBJS)
	@mkdir -p $(BIN_DIR)
	$(COMPILER) $(FLAGS) $^ -o $@

$(BIN_DIR)/binomial.out: $(BINOMIAL_OBJS)
	@mkdir -p $(BIN_DIR)
	$(COMPILER) $(FLAGS) $^ -o $@

# Rule to compile .cpp files to .o files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(COMPILER) $(FLAGS) -c $< -o $@

# Rule to clean the build
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Phony targets (not actual files)
.PHONY: all clean
