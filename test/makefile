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
CXXFLAGS = -g -Wall -Wextra -std=c++11 -O0
CXXFLAGS += $(GTFLAGS) $(INCDIR)

# Dependencies for each unit test program.
OBJ_BASICTYPES = tbasictypes.o basictypes.o
OBJ_BASICBOARD = tbasicboard.o basicboard.o basictypes.o
OBJ_PIECECODE = tpiececode.o piececode.o
OBJ_BOARDINFO = tboardinfo.o
OBJ_PIECECOUNT = tpiececount.o piececount.o board.o square.o \
                 piecemove.o piececode.o
OBJ_SQUARE = tsquare.o square.o piececode.o
OBJ_PIECEMOVE = tpiecemove.o piecemove.o square.o piececode.o
OBJ_FENRECORD = tfenrecord.o board.o piecemove.o square.o piececode.o
OBJ_IOFEN = tiofen.o fennotation.o board.o piecemove.o \
            square.o piececode.o piececount.o
OBJ_BOARD = tboard.o board.o piecemove.o square.o piececode.o

# Combine unique object files.
OBJ_LIST := $(sort $(OBJ_BASICTYPES) $(OBJ_BASICBOARD) $(OBJ_PIECECODE) \
              $(OBJ_PIECECOUNT) $(OBJ_SQUARE) $(OBJ_PIECEMOVE) $(OBJ_BOARD) \
              $(OBJ_BOARDINFO) $(OBJ_FENRECORD) $(OBJ_IOFEN))

# Unit test programs.
TARGETS = tbasictypes tbasicboard tpiececode tboardinfo tpiececount \
          tsquare tpiecemove tboard tfenrecord tiofen

all: $(TARGETS)

tbasictypes: $(OBJ_BASICTYPES)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(LFLAGS) -o $@

tbasicboard: $(OBJ_BASICBOARD)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(LFLAGS) -o $@

tpiececode: $(OBJ_PIECECODE)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(LFLAGS) -o $@

tboardinfo: $(OBJ_BOARDINFO)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(LFLAGS) -o $@

tpiececount: $(OBJ_PIECECOUNT)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(LFLAGS) -o $@

tsquare: $(OBJ_SQUARE)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(LFLAGS) -o $@

tpiecemove: $(OBJ_PIECEMOVE)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(LFLAGS) -o $@

tfenrecord: $(OBJ_FENRECORD)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(LFLAGS) -o $@

tiofen: $(OBJ_IOFEN)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(LFLAGS) -o $@

tboard: $(OBJ_BOARD)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(LFLAGS) -o $@

# Header dependencies.
$(OBJ_BASICTYPES): basictypes.hh
$(OBJ_BASICBOARD): basicboard.hh basictypes.hh
$(OBJ_PIECECODE): piececode.hh
$(OBJ_BOARDINFO): boardinfo.hh
$(OBJ_PIECECOUNT): piececount.hh piececode.hh
$(OBJ_SQUARE): square.hh piececode.hh
$(OBJ_PIECEMOVE): piecemove.hh square.hh piececode.hh
$(OBJ_FENRECORD): fenrecord.hh board.hh
$(OBJ_IOFEN): fennotation.hh fenrecord.hh board.hh
$(OBJ_BOARD): board.hh piecemove.hh square.hh piececode.hh

.PHONY: run clean
# Run all unit tests.
run: $(TARGETS)
	-@./runtest.py $^

clean:
	$(RM) $(OBJ_LIST) $(TARGETS) 2>/dev/null
