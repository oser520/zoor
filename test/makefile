VPATH = .:../src
INCDIR = -I../src

GTFLAGS = -isystem $(GTEST_DIR)/include -I$(GTEST_DIR)

LDFLAGS  = -L/opt/googletest
LFLAGS   = -lgtest

CXXFLAGS = -Wall -Wextra -std=c++11 -pthread
CXXFLAGS += $(GTFLAGS) $(INCDIR)

OBJ = tsquare.o

all: tsquare

tsquare: $(OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $< $(LFLAGS) -o $@

$(OBJ): $(OBJ:.o=.hh)
