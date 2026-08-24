CXX = g++
AR = ar
ARFLAGS = rcs
LDDIR = 
LDFLAGS =
TESTFLAGS = -lgtest -lgtest_main -lpthread
INCLDDIR = -Iinclude
DEBUGFLAGS = -g
CXXFLAGS = -std=c++17 -pedantic -Wfatal-errors -Wconversion -Wredundant-decls -Wshadow -Wall -Wextra
BINFLAGS =

LIB = bin/libmatrix.a
APP = bin/matrix
SRCDIR = src
SRC = $(shell find $(SRCDIR) -name "*.cpp")
OBJDIR = obj
OBJ = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC))

# Configuration de tests unitaires avec GTest
TESTDIR = tests
TESTSRC = $(shell find $(TESTDIR) -name "*.cpp")
TESTOBJ = $(patsubst $(TESTDIR)/%.cpp, $(OBJDIR)/$(TESTDIR)/%.o, $(TESTSRC))
TESTAPP = bin/run_tests

# On exclut main.o lors de la liaison des tests
OBJ_NO_MAIN = $(filter-out $(OBJDIR)/main.o, $(OBJ))

.PHONY: all run clean debug doc init lib test

# Compilation du binaire simple
all: $(OBJ)
	@mkdir -p bin
	$(CXX) $(LDDIR) -o $(APP) $^ $(BINFLAGS) $(CXXFLAGS) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(DEBUGFLAGS) -c $(INCLDDIR) $< -o $@

# Compilation du binaire en tant que librairie.
$(LIB): $(OBJ_NO_MAIN)
	@mkdir -p bin
	$(AR) $(ARFLAGS) $@ $^

# Compilation du binaire de test avec GTest
$(TESTAPP): $(OBJ_NO_MAIN) $(TESTOBJ)
	@mkdir -p bin
	$(CXX) $(LDDIR) -o $@ $^ $(BINFLAGS) $(CXXFLAGS) $(LDFLAGS) $(TESTFLAGS)

$(OBJDIR)/$(TESTDIR)/%.o: $(TESTDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(DEBUGFLAGS) $(INCLDDIR) -c $< -o $@

run: 
	$(APP)

lib: $(LIB)

test: $(TESTAPP)
	$(TESTAPP)

clean:
	find $(OBJDIR) -type f -name "*.o" -delete

debug:
	gdb $(APP)

doc:
	doxygen Doxyfile

init:
	mkdir -p bin
	mkdir -p obj
