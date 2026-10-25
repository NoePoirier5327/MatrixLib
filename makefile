CXX = g++
AR = ar
ARFLAGS = rcs
DEFAULT_LDFLAGS = 
LDFLAGS = 
TESTFLAGS = -lgtest -lgtest_main -lpthread
DEFAULT_CXXFLAGS = -std=c++17 -pedantic -Wfatal-errors -Wconversion -Wredundant-decls -Wshadow -Wall -Wextra
CXXFLAGS = 
INCLUDE_DIR = 
BINFLAGS =

CXXLIB = lib/libmatrix.a
LUALIB = lua/matrix.so
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
OBJ_LUA_LIB = $(filter-out $(OBJDIR)/main.o, $(OBJ))
OBJ_WITHOUT_LUA = $(filter-out $(OBJDIR)/lua.o, $(OBJ))
OBJ_CXX_LIB = $(filter-out $(OBJDIR)/main.o $(OBJDIR)/lua.o, $(OBJ))
OBJ_TEST = $(filter-out $(OBJDIR)/main.o $(OBJDIR)/lua.o, $(OBJ))

.PHONY: all run clean debug doc init lib test release

# Compilation du binaire simple
all: CXXFLAGS := $(DEFAULT_CXXFLAGS)
all: LDFLAGS := $(DEFAULT_LDFLAGS)
all: $(APP)

$(APP): $(OBJ_WITHOUT_LUA)
	@mkdir -p bin
	$(CXX) -o $(APP) $^ $(BINFLAGS) $(CXXFLAGS) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $(INCLUDE_DIR) $< -o $@

# Compilation du binaire en tant que librairie.
$(CXXLIB): $(OBJ_CXX_LIB)
	@mkdir -p lib
	@rm -rR include
	@mkdir -p include
	cp -rR $(SRCDIR)/matrix/ include
	find include -type f -name "*.cpp" -delete
	$(AR) $(ARFLAGS) $@ $^

$(LUALIB): $(OBJ_LUA_LIB)
	@mkdir -p lua
	$(CXX) -o $@ $^ $(LDFLAGS)

# Compilation du binaire de test avec GTest
$(TESTAPP): $(OBJ_TEST) $(TESTOBJ)
	@mkdir -p bin
	$(CXX) -o $@ $^ $(BINFLAGS) $(CXXFLAGS) $(LDFLAGS) $(TESTFLAGS)

$(OBJDIR)/$(TESTDIR)/%.o: $(TESTDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: 
	$(APP)

lib: CXXFLAGS := $(DEFAULT_CXXFLAGS) -DNDEBUG
lib: LDFLAGS := $(DEFAULT_LDFLAGS)
lib: clean $(CXXLIB) test

lua: INCLUDE_DIR := -I/usr/include/lua5.4
lua: LDFLAGS := $(DEFAULT_LDFLAGS) -shared -llua5.4
lua: CXXFLAGS := $(DEFAULT_CXXFLAGS) -DNDEBUG -fPIC
lua: clean $(LUALIB) test

test: CXXFLAGS := $(DEFAULT_CXXFLAGS) -g
test: INCLUDE_DIR := 
test: LDFLAGS := $(DEFAULT_LDFLAGS)
test: clean $(TESTAPP)
	$(TESTAPP)

clean:
	find $(OBJDIR) -type f -name "*.o" -delete

debug: CXXFLAGS += -g -DDEBUG
debug: clean $(APP)
	gdb $(APP)

doc:
	doxygen Doxyfile

init:
	mkdir -p bin
	mkdir -p obj
