CXX := gcc
CXXFLAGS := -g -Wall -W -Werror -fsanitize=address
TARGET := intarray.out

SRC := int_array.c main.c
OBJ := $(SRC:.c=.o)
DEPS := int_array.h quicksort.h

$(TARGET): $(OBJ)
	@$(CXX) $(CXXFLAGS) $^ -o $@
		@echo "$(GC)Executable built successfully -> $@ $(NC)"

%.o: %.c $(DEPS)
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "$(CC)Object built -> $@$(NC)"

clean:
	@rm -f $(OBJ) $(TARGET)
	@echo "$(BC)Cleaned.$(NC)"

run: $(TARGET)
	@./$(TARGET)

.PHONY: all test clean run

NC := \033[0m
GC := \033[32m
MC := \033[35m
BC := \033[34m
CC := \033[36m