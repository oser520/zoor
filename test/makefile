VPATH = .:../src
INCDIR = -I../src

GTFLAGS = -isystem $(GTEST_DIR)/include

LDFLAGS  = -L/opt/googletest
LFLAGS   = -lgtest -lpthread

CXXFLAGS = -Wall -Wextra -std=c++11 -O2
CXXFLAGS += $(GTFLAGS) $(INCDIR)

OBJ_PIECECODE = tpiececode.o piececode.o
OBJ_SQUARE = tsquare.o square.o piececode.o
TARGETS = tpiececode tsquare

all: $(TARGETS)

tpiececode: $(OBJ_PIECECODE)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(LFLAGS) -o $@

tsquare: $(OBJ_SQUARE)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(LFLAGS) -o $@

$(OBJ_PIECECODE): piececode.hh

$(OBJ_SQUARE): square.hh piececode.hh

.PHONY: run clean
run: tsquare tpiececode
	@echo 
	@echo Running Unit Tests for Square
	@echo 
	-@./tpiececode
	@echo
	@echo Unit Tests for Square Finished!
	@echo 
	@echo Running Unit Tests for PieceCode, PieceColor, PieceValue
	@echo 
	-@./tsquare
	@echo
	@echo Unit Tests for PieceCode, PieceColor, PieceValue Finished!
	@echo 

clean:
	$(RM) $(OBJ_SQUARE) $(OBJ_PIECECODE) $(TARGETS) 2>/dev/null
