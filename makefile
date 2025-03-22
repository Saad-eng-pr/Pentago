# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c11

# Linker flags
LDFLAGS = -lSDL2 -lSDL2_image

# Source files
SRCS = game.c minmax.c SDL.c

# Header files
HDRS = Pentago.h

# Object files
OBJS = $(SRCS:.c=.o)

# Executable
TARGET = pentago

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Compile source files to object files
%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
