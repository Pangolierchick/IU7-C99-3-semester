CC = clang
CF = -Wall -Werror -std=gnu99 -I ../inc/ -I ../inc/libarr

OS = $(shell uname -s)

ifeq ($(OS), Darwin)
	PYTHON := python3
	CF += -DOSX
	LF := -dynamiclib -fvisibility=hidden -current_version 1.0 -compatibility_version 1.0
	LIBAR_LIB := libar.dylib
else
	PYTHON := python3
	LF := -shared
	CF += -fPIC -DLinux
	LIBAR_LIB := libar.so
endif

LIBARR_SRC = ./libarr/libarr.c
LIBARR_HEAD = ../inc/libarr/*.h

LIB_DIR = $(shell cd .. & pwd)/lib

build_libs: $(info building for $(OS))cr_lib_dir $(LIB_DIR)/$(LIBAR_LIB) create_lib_link

create_lib_link:
	$(shell ln -sf $(LIB_DIR)/$(LIBAR_LIB) /usr/local/lib)

build_py_ext: build_libs
	$(PYTHON) setup.py install

cr_lib_dir:
	@mkdir -p $(LIB_DIR)

clean_tmps:
	rm -rf build

clean_lib:
	rm -rf $(LIB_DIR)

$(LIB_DIR)/$(LIBAR_LIB): $(LIBARR_SRC) $(LIBARR_HEAD)
	$(CC) $(CF) $(LF) $< -o $@

