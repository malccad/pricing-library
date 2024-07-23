# The compiler to use
COMPILER = clang++

# Compiler flags
FLAGS = -std=c++14

TARGETS = finite_difference.out monte_carlo.out binomial.out
# List of source files
FINITE_DIFF_SRCS = finite_difference_main.cpp src/crank_nicolson.cpp \
	src/explicit_numerical.cpp src/implicit_numerical_base.cpp src/implicit_vanilla.cpp \
	src/matrix_solver.cpp src/numerical_pricing_engine_factory.cpp src/numerical_pricing_engine_registration.cpp \
	src/numerical_pricing_engine.cpp src/option.cpp src/payoff_factory.cpp src/payoff_registration.cpp \
	src/payoff.cpp src/utils.cpp
FINITE_DIFF_OBJS = $(FINITE_DIFF_SRCS:.cpp=.o)

MONTE_CARLO_SRCS = monte_carlo_main.cpp src/box_muller.cpp src/gaussian_generator.cpp \
	src/halton_sequence.cpp src/monte_carlo_pricing.cpp src/option.cpp src/payoff_factory.cpp \
	src/payoff_registration.cpp src/payoff.cpp src/utils.cpp
MONTE_CARLO_OBJS = $(MONTE_CARLO_SRCS:.cpp=.o)

BINOMIAL_SRCS = binomial_main.cpp src/binomial_pricing.cpp src/option.cpp src/payoff_factory.cpp \
	src/payoff_registration.cpp src/payoff.cpp src/utils.cpp
BINOMIAL_OBJS = $(BINOMIAL_SRCS:.cpp=.o)

# Default target
all: $(TARGETS)

# Rule to link the object files to create the executable
finite_difference.out: $(FINITE_DIFF_OBJS)
	$(COMPILER) $(FLAGS) $^ -o $@

monte_carlo.out: $(MONTE_CARLO_OBJS)
	$(COMPILER) $(FLAGS) $^ -o $@

binomial.out: $(BINOMIAL_OBJS)
	$(COMPILER) $(FLAGS) $^ -o $@

# Rule to compile .cpp files to .o files
%.o: %.cpp
	$(COMPILER) $(FLAGS) -c $< -o $@

# Rule to clean the build
clean:
	rm -f $(FINITE_DIFF_OBJS) $(MONTE_CARLO_OBJS) $(BINOMIAL_OBJS) $(TARGETS)$

# Phony targets (not actual files)
.PHONY: all clean
