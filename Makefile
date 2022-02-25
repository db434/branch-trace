ifdef PIN_ROOT
  CONFIG_ROOT := $(PIN_ROOT)/source/tools/Config
  include $(CONFIG_ROOT)/makefile.config
  include $(TOOLS_ROOT)/Config/makefile.default.rules
else
  $(error Please provide the location of Pin in PIN_ROOT)
endif

# Set this on the command line to build a different tool.
SRC_FILE ?= branch_trace.cpp

OUT_FILE  = $(SRC_FILE:.cpp=.so)

# Need to use fake names for all the rules to avoid name clashes with Pin's
# Makefiles.
.PHONY: all tool clean-all

all: tool

tool: $(SRC_FILE) | $(OBJDIR)
	$(MAKE) TARGET=intel64 $(OBJDIR)$(OUT_FILE)

clean-all:
	$(MAKE) TARGET=intel64 clean

