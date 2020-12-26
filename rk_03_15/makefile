CC = gcc
CF = -Wall -std=c99 -I ./inc

OBJDIR = ./out
SRCDIR = ./src
INCDIR = ./inc

DEPS = $(wildcard $(INCDIR)/*.h)
SRC = $(wildcard $(SRCDIR)/*.c)
TEMP = $(patsubst %.c, %.o, $(SRC))
OBJECTS = $(patsubst $(SRCDIR)%, $(OBJDIR)%, $(TEMP))

build: objdir main

run:
	./main in.txt

main: $(OBJECTS)
	$(CC) $(CF) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) $(CF) -c $< -o $@

objdir:
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)
	rm -rf ./main
