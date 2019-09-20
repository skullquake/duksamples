FILTER_OUT = $(foreach v,$(2),$(if $(findstring $(1),$(v)),,$(v)))
OS=$(shell $(CXX) -dumpmachine)
ifneq (,$(findstring mingw,$(OS)))
SOEXT?=.dll
BINEXT?=.exe
else
SOEXT?=.so
BINEXT?=
endif
ifeq ($(PREFIX),)
PREFIX := /usr/local
endif
CC=gcc
CXX=g++
AR=ar
BUILDDIR=./bin
BUILDDIRBIN=./bin/app
BUILDDIRLIB=./bin/lib
BIN=./bin/duk$(BINEXT)
SRCDIRBIN=./src/app
LINENOISE=OFF
MODULES=ON
CONSOLE=ON
PRINTALERT=ON
FILEIO=ON
CFLAGS=\
	-I./include/app\
	-I./include/app/duktape\
	-I./include/app/duktape/extras/console\
	-I./include/app/duktape/extras/module-duktape\
	-I./include/app/duktape/extras/module-node\
	-I./include/app/duktape/extras/print-alert
ifeq ($(LINENOISE),ON)
SRCBIN=$(shell find $(SRCDIRBIN) -name "*.cpp" -o -name "*.c" )
CFLAGS+=\
	-DDUK_CMDLINE_LINENOISE\
	-DDUK_CMDLINE_FANCY\
       	-I./include/linenoise
else
SRCBIN=$(call FILTER_OUT,linenoise,$(shell find $(SRCDIRBIN) -name "*.cpp" -o -name "*.c" ))
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
OBJSBIN=$(addprefix $(BUILDDIRBIN)/,$(patsubst %.c,%.o ,$(patsubst %.cpp,%.o,$(SRCBIN))))
LDFLAGS=\

LIB=./lib/a$(SOEXT)
SRCDIRLIB=src/lib
SRCLIB=$(shell find $(SRCDIRLIB) -name "*.cpp" -o -name "*.c" )
OBJSLIB=$(addprefix $(BUILDDIRLIB)/,$(patsubst %.c,%.o ,$(patsubst %.cpp,%.o,$(SRCLIB))))

all:\
	$(BIN)
$(BIN):$(OBJSBIN) $(LIB)
	@printf "generating $@...\n"
	@mkdir -p $(@D)
	$(CXX)\
		$(CFLAGS)\
		$(OBJSBIN)\
		$(LDFLAGS)\
		-o $(BIN)
$(BUILDDIRBIN)/%.o: %.cpp
	@printf "generating $@...\n"
	@mkdir -p $(@D)
	$(CXX)\
		$(CFLAGS)\
		-c $<\
		$(LDFLAGS)\
		-o $@
$(BUILDDIRBIN)/%.o: %.c
	@printf "generating $@...\n"
	@mkdir -p $(@D)
	$(CC)\
		$(CFLAGS)\
		-c $<\
		$(LDFLAGS)\
		-o $@
$(LIB):$(OBJSLIB)
	@mkdir -p $(@D)
	$(CXX)\
		$(CFLAGSLIB)\
		$(OBJSLIB)\
		-shared\
		$(LDFLAGSLIB)\
		-o $(LIB)
$(BUILDDIRLIB)/%.o: %.cpp
	@printf "generating $@...\n"
	@mkdir -p $(@D)
	$(CXX)\
		$(CFLAGSLIB)\
		-c $<\
		-fPIC\
		$(LDFLAGSLIB)\
		-o $@
$(BUILDDIRLIB)/%.o: %.c
	@printf "generating $@...\n"
	@mkdir -p $(@D)
	$(CC)\
		$(CFLAGSLIB)\
		-c $<\
		-fPIC\
		$(LDFLAGSLIB)\
		-o $@

.phony:\
	run\
	clean\
	lsvar
clean:
	@rm -r ./bin ./lib
install:
	@cp $(BIN) /usr/bin
run:
	$(BIN)
lsvar:
	@echo $(CFLAGS)
	@echo $(BIN)
	@echo $(OBJS)
	@echo $(SRC)
	@echo $(SRCDIR)
	@echo $(PREFIX)




