# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g

# Shared source files
SHARED_SRC = utils.c
SHARED_OBJ = $(SHARED_SRC:.c=.o)

# Independent source files
LEXAN_SRC = lexan.c
SPLITTER_SRC = splitter.c
BUILDER_SRC = builder.c

# Executable names
LEXAN_EXEC = lexan
SPLITTER_EXEC = splitter
BUILDER_EXEC = builder

# Targets
all: $(LEXAN_EXEC) $(SPLITTER_EXEC)
# all: $(LEXAN_EXEC) $(SPLITTER_EXEC) $(BUILDER_EXEC)

# Build the lexan executable
$(LEXAN_EXEC): $(LEXAN_SRC) $(SHARED_OBJ)
	$(CC) $(CFLAGS) -o $(LEXAN_EXEC) $(LEXAN_SRC) $(SHARED_OBJ)

# Build the splitter executable
$(SPLITTER_EXEC): $(SPLITTER_SRC) $(SHARED_OBJ)
	$(CC) $(CFLAGS) -o $(SPLITTER_EXEC) $(SPLITTER_SRC) $(SHARED_OBJ)

# Build the builder executable
$(BUILDER_EXEC): $(BUILDER_SRC) $(SHARED_OBJ)
	$(CC) $(CFLAGS) -o $(BUILDER_EXEC) $(BUILDER_SRC) $(SHARED_OBJ)

# Compile shared object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up compiled files
clean:
	rm -f *.o $(LEXAN_EXEC) $(SPLITTER_EXEC) $(BUILDER_EXEC)

# Rebuild everything
rebuild: clean all

# Test target (example of running tests)
run:
	./lexan -i ./Data4Proj2_ascii/GreatExpectations_a.txt -l 3 -m 2 -t 5 -e ./Data4Proj2_ascii/ExclusionList1_a.txt -o test.txt

# Valgrind
# valgrind --leak-check=full --track-origins=yes --verbose ./lexan -i ./Data4Proj2_ascii/GreatExpectations_a.txt -l 3 -m 2 -t 5 -e ./Data4Proj2_ascii/ExclusionList1_a.txt -o test.txt