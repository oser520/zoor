# file: makefile
# author: Omar A Serrano 
# date: 2016-01-06
#
# makefile for building unit tests.

SHELL = /bin/sh

# Source and include directories.
VPATH = .:../src
INCDIR = -I../src

# Include directory for googletest.
GTFLAGS = -isystem $(GTEST_DIR)/include

# Paths for libraries, and libraries used.
LDFLAGS  = -L/opt/googletest
LFLAGS   = -lgtest -lpthread

# Compiler flags.
CXXFLAGS = -Wall -Wextra -std=c++11 -O2
CXXFLAGS += $(GTFLAGS) $(INCDIR)

# Dependencies for each unit test program.
OBJ_PIECECODE = tpiececode.o piececode.o
OBJ_PIECECOUNT = tpiececount.o piececount.o piececode.o
OBJ_SQUARE = tsquare.o square.o piececode.o

# Unit test programs.
TARGETS = tpiececode tpiececount tsquare

all: $(TARGETS)

tpiececode: $(OBJ_PIECECODE)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(LFLAGS) -o $@

tpiececount: $(OBJ_PIECECOUNT)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(LFLAGS) -o $@

tsquare: $(OBJ_SQUARE)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(LFLAGS) -o $@

# Header dependencies.
$(OBJ_PIECECODE): piececode.hh
$(OBJ_PIECECOUNT): piececode.hh piececode.hh
$(OBJ_SQUARE): square.hh piececode.hh

.PHONY: run clean
# Run all unit tests.
run: $(TARGETS)
	$(foreach target,$^,$(shell echo $(shell ./$(target))))

clean:
	$(RM) $(OBJ_SQUARE) $(OBJ_PIECECODE) $(OBJ_PIECECOUNT) $(TARGETS) 2>/dev/null
