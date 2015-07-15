.PHONY: clean all
.SECONDARY:

# EDIT THIS SECTION

CPP        = g++
SRC_SUFFIX = cxx
INCLUDES   = include
CFLAGS     = -Wall -Wextra -pedantic -std=c++11 -O3 -g
LINKFLAGS  =

# EVERYTHING PAST HERE SHOULD WORK AUTOMATICALLY

INCLUDES := $(addprefix -I,$(INCLUDES))
CFLAGS	 += $(INCLUDES)

EXECUTABLES = $(patsubst usage/%.cc,bin/%,$(wildcard usage/*.cc))
O_FILES = $(patsubst %.cc,build/%.o,$(wildcard src/*.cc))

all: $(EXECUTABLES)

bin/%: build/usage/%.o $(O_FILES)
	@echo "Compiling $@"
	@mkdir -p $(dir $@)
	@$(CPP) $(LINKFLAGS) $^ -o $@

build/%.o: %.cc
	@echo "Compiling $@"
	@mkdir -p $(dir $@)
	@$(CPP) -c $(CFLAGS) $< -o $@

-include $(shell find build -name "*.d" 2> /dev/null)

clean:
	@echo "Cleaning up"
	@rm -rf build
	@rm -rf bin
