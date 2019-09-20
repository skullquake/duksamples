FILTER_OUT = $(foreach v,$(2),$(if $(findstring $(1),$(v)),,$(v)))
OS=$(shell $(CXX) -dumpmachine)
ifneq (,$(findstring mingw,$(OS)))
SOEXT?=dll
BINEXT?=exe
else
SOEXT?=so
BINEXT?=out
endif
ifeq ($(PREFIX),)
PREFIX := /usr/local
endif
CC=gcc
CXX=g++
AR=ar
BUILDDIR=./bin/build
BIN=./bin/duk.$(BINEXT)
SOURCEDIR=src
LINENOISE=OFF
MODULES=ON
CONSOLE=ON
PRINTALERT=ON
FILEIO=ON
CFLAGS=\
	-I./include\
	-I./include/duktape\
	-I./include/duktape/extras/console\
	-I./include/duktape/extras/module-duktape\
	-I./include/duktape/extras/module-node\
	-I./include/duktape/extras/print-alert
ifeq ($(LINENOISE),ON)
SOURCES=$(shell find $(SOURCEDIR) -name "*.cpp" -o -name "*.c" )
CFLAGS+=\
	-DDUK_CMDLINE_LINENOISE\
	-DDUK_CMDLINE_FANCY\
       	-I./include/linenoise
else
SOURCES=$(call FILTER_OUT,linenoise,$(shell find $(SOURCEDIR) -name "*.cpp" -o -name "*.c" ))
endif
ifeq ($(MODULES),ON)
CFLAGS+=\
	-DDUK_CMDLINE_MODULE_SUPPORT
endif
ifeq ($(CONSOLE),ON)
CFLAGS+=\
	-DDUK_CMDLINE_CONSOLE_SUPPORT
endif
ifeq ($(PRINTALERT),ON)
CFLAGS+=\
	-DDUK_CMDLINE_PRINTALERT_SUPPORT
endif
ifeq ($(FILEIO),ON)
CFLAGS+=\
	-DDUK_CMDLINE_FILEIO
endif
OBJECTS=$(addprefix $(BUILDDIR)/,$(patsubst %.c,%.o ,$(patsubst %.cpp,%.o,$(SOURCES))))
LDFLAGS=\

all:\
	$(BIN)
$(BIN):$(OBJECTS)
	$(CXX)\
		$(CFLAGS)\
		$(OBJECTS)\
		$(LDFLAGS)\
		-o $(BIN)
$(BUILDDIR)/%.o: %.cpp
	@printf "generating $@...\n"
	@mkdir -p $(@D)
	$(CXX)\
		$(CFLAGS)\
		-c $<\
		$(LDFLAGS)\
		-o $@
$(BUILDDIR)/%.o: %.c
	@printf "generating $@...\n"
	@mkdir -p $(@D)
	$(CC)\
		$(CFLAGS)\
		-c $<\
		$(LDFLAGS)\
		-o $@
.phony:\
	run\
	clean\
	lsvar
clean:
	@rm -r ./bin
install:
	@cp $(BIN) /usr/bin
run:
	$(BIN)
lsvar:
	@echo $(CFLAGS)
	@echo $(BIN)
	@echo $(OBJECTS)
	@echo $(SOURCES)
	@echo $(SRCDIR)
	@echo $(PREFIX)




