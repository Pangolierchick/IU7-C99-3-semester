CC = gcc
CF = -g3 -Wall -Wextra -pedantic -std=gnu99 -I ./inc -I ./inc/palib -I ./inc/flib -I ./inc/arlib
UNITF = $(CF) -lcheck -lpthread

CUR_DIR = $(shell pwd)


OBJDIR = ./out
SRCDIR = ./src
DEPSDIR = ./inc
UNITDIR = ./unit_tests
LIBDIR = lib

DEPS = $(wildcard $(DEPSDIR)/*.h)
SRC = $(wildcard $(SRCDIR)/*.c)
TEMPSRC = $(patsubst %.c, %.o, $(SRC))
UNIT = $(wildcard $(UNITDIR)/*.c)
TEMPUNIT = $(patsubst %.c, %.o, $(UNIT))
SRCOBJECTS = $(patsubst $(SRCDIR)%, $(OBJDIR)%, $(TEMPSRC))
UNITOBJECTS = $(patsubst $(UNITDIR)%, $(OBJDIR)%, $(TEMPUNIT))

OBJECTS = $(OBJDIR)/funcs.o $(OBJDIR)/file.o $(UNITOBJECTS)

MAINNAME = app.exe
UNITNAME = unit_tests.exe

LIBS = $(wildcard $(CUR_DIR)/lib/*)

compile: compile_libs objdir $(MAINNAME)

compile_libs:
	make -C src build_libs

$(MAINNAME): $(SRCOBJECTS)
	$(CC) $(CF) $(LF) $(LIBS) $^ -o $@
	@echo "Build done."

objdir:
	@mkdir -p $(OBJDIR)

clean:
	rm -rf $(MAINNAME) $(OBJDIR)
	rm -rf ./$(UNITNAME)
	rm -rf ./tests_res
	rm -rf ./test_build
	rm -rf ./out.txt
	@echo "Cleaned!"

clean_libs:
	make -C src clean_lib

uninstall: clean_libs clean
 
unit: objdir $(UNITNAME) run_unit

$(UNITNAME): $(OBJECTS)
	echo "In progress"

run_unit:
	./$(UNITNAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	@mkdir -p $(OBJDIR)
	$(CC) $(CF) $< -c -o $@


func:
	./init_tests
