CC = clang
CF = -Wall -Werror -std=gnu99 -I ../inc/

OS = $(shell uname -s)
ROOT_DIR = $(shell cd .. && pwd)

# -install_name $(ROOT_DIR)/lib

ifeq ($(OS), Darwin)
	LF := -dynamiclib -fvisibility=hidden 
	CF += -DOSX

	PALIB_LIB = libpa.dylib
	FLIB_LIB = libf.dylib 
	ARLIB_LIB = libar.dylib 
else 
	LF := -shared
	CF += -fPIC -DLinux

	PALIB_LIB = libpa.so
	FLIB_LIB = libf.so 
	ARLIB_LIB = libar.so
endif

PALIB_SRC = ./palib/palib.c
PALIB_HEAD = ../inc/palib/*.h

FLIB_SRC = ./flib/flib.c
FLIB_HEAD = ../inc/flib/*.h

ARLIB_SRC = ./arlib/arlib.c
ARLIB_HEAD = ../inc/arlib/*.h

LIB_DIR = $(ROOT_DIR)/lib



cr_lib_dir:
	@mkdir -p $(LIB_DIR)

build_libs: $(info building for $(OS))cr_lib_dir $(LIB_DIR)/$(PALIB_LIB) $(LIB_DIR)/$(FLIB_LIB) $(LIB_DIR)/$(ARLIB_LIB)

clean_lib:
	rm -rf $(LIB_DIR)

$(LIB_DIR)/$(PALIB_LIB): $(PALIB_SRC) $(PALIB_HEAD)
	$(CC) $(CF) $(LF) -I ../inc/palib $< -o $@

$(LIB_DIR)/$(FLIB_LIB): $(FLIB_SRC) $(FLIB_HEAD)
	$(CC) $(CF) $(LF) -I ../inc/flib $< -o $@

$(LIB_DIR)/$(ARLIB_LIB): $(ARLIB_SRC) $(ARLIB_HEAD)
	$(CC) $(CF) $(LF) -I ../inc/arlib $< -o $@

