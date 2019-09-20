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
BIN=./bin/a.$(BINEXT)
SOURCEDIR=src
LINENOISE=OFF
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
run:
	$(BIN)
lsvar:
	@echo $(BIN)
	@echo $(OBJECTS)
	@echo $(SOURCES)
	@echo $(SRCDIR)
	@echo $(PREFIX)




