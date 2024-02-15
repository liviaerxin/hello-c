CC = gcc
CFLAGS = -Wall -std=c99

# Get all source files with a .c file extension
SOURCES = $(wildcard *.c)

# Replace .c with .o for object files
OBJECTS = $(SOURCES:.c=.o)

# Define the executables based on the source files
EXECUTABLES = $(SOURCES:.c=.out)

all: $(EXECUTABLES)

# Rule to build each executable
%.out: %.o
	$(CC) $(CFLAGS) $< -o $@

# Rule to build object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLES)