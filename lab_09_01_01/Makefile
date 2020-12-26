CC = gcc
CF = -g3 -Wall -Wextra -pedantic -std=gnu99 -I ./inc
UNITF = $(CF) -lcheck -lpthread

OBJDIR = ./out
SRCDIR = ./src
DEPSDIR = ./inc
UNITDIR = ./unit_tests

DEPS = $(wildcard $(DEPSDIR)/*.h)
SRC = $(wildcard $(SRCDIR)/*.c)
TEMPSRC = $(patsubst %.c, %.o, $(SRC))
UNIT = $(wildcard $(UNITDIR)/*.c)
TEMPUNIT = $(patsubst %.c, %.o, $(UNIT))
SRCOBJECTS = $(patsubst $(SRCDIR)%, $(OBJDIR)%, $(TEMPSRC))
UNITOBJECTS = $(patsubst $(UNITDIR)%, $(OBJDIR)%, $(TEMPUNIT))

ALL_OBJECTS = $(SRCOBJECTS) $(UNITOBJECTS)

OBJECTS = $(filter-out $(OBJDIR)/main.o, $(ALL_OBJECTS))

MAINNAME = app.exe
UNITNAME = unit_tests.exe

compile: objdir $(MAINNAME)


$(MAINNAME): $(SRCOBJECTS)
	$(CC) $(CF) $^ -o $@
	@echo "Build done."

objdir:
	@mkdir -p $(OBJDIR)

clean:
	rm -rf *.dSYM
	rm -rf $(MAINNAME) $(OBJDIR)
	rm -rf ./$(UNITNAME)
	rm -rf ./tests_res
	rm -rf ./test_build
	rm -rf ./out.txt
	@echo "Cleaned!"
 
unit: objdir $(UNITNAME) run_unit

$(UNITNAME): $(OBJECTS)
	@mkdir -p $(OBJDIR)
	$(CC) $(UNITF) $^ -o $@

run_unit:
	./$(UNITNAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	@mkdir -p $(OBJDIR)
	$(CC) $(CF) $< -c -o $@

$(OBJDIR)/%.o: $(UNITDIR)/%.c $(DEPS)
	@mkdir -p $(OBJDIR)
	$(CC) $(CF) $< -c -o $@

func:
	./init_tests
