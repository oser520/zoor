VPATH = .:../src
INCDIR = -I../src

GTFLAGS = -isystem $(GTEST_DIR)/include

LDFLAGS  = -L/opt/googletest
LFLAGS   = -lgtest -lpthread

CXXFLAGS = -Wall -Wextra -std=c++11
CXXFLAGS += $(GTFLAGS) $(INCDIR)

OBJ = tsquare.o square.o piececode.o

all: tsquare

tsquare: $(OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(LFLAGS) -o $@

$(OBJ): square.hh piececode.hh
