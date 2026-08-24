CXX = g++
LDDIR = 
LDFLAGS =
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

all: $(OBJ)
	@mkdir -p bin
	$(CXX) $(LDDIR) -o $(APP) $^ $(BINFLAGS) $(CXXFLAGS) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(DEBUGFLAGS) -c $(INCLDDIR) $< -o $@

run: 
	$(APP)

clean:
	find $(OBJDIR) -type f -name "*.o" -delete

debug:
	gdb $(APP)

doc:
	doxygen Doxyfile

init:
	mkdir -p bin
	mkdir -p obj
