VPATH = .:../src
INCDIR = -I../src

GTFLAGS = -isystem $(GTEST_DIR)/include

LDFLAGS  = -L/opt/googletest
LFLAGS   = -lgtest -lpthread

CXXFLAGS = -Wall -Wextra -std=c++11
CXXFLAGS += $(GTFLAGS) $(INCDIR)

OBJ = tsquare.o square.o piececode.o

all: run tsquare

run: tsquare
	@echo Running Unit Tests for Square
	@echo 
	@./tsquare
	@echo
	@echo Unit Tests for Square are done

tsquare: $(OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(LFLAGS) -o $@

$(OBJ): square.hh piececode.hh

.PHONY: clean
clean:
	$(RM) $(OBJ) tsquare 2>/dev/null
