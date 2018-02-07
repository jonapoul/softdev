CC      = g++ -std=c++11
CCFLAGS = -c -Wall
LDFLAGS = -Wall

ROOTDIR := $(shell pwd)
OBJDIR  := $(ROOTDIR)/obj
BINDIR  := $(ROOTDIR)/bin
SRCDIR  := $(ROOTDIR)/src
INCDIR  := $(ROOTDIR)/inc
LIBS     =

INC  = -I$(INCDIR)
SRC := $(wildcard $(SRCDIR)/*.cpp)
OBJ := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRC))

PCH_SRC = $(INCDIR)/pch.h
PCH_OUT = $(OBJDIR)/pch.h.gch

EXEC = main

default: $(EXEC)

$(EXEC): $(OBJ) | $(BINDIR)
	@echo $(OBJ)
	$(CC) $(LDFLAGS) $(INC) $^ -o $(BINDIR)/$@ $(LIBS)

$(OBJDIR):
	mkdir -p $(OBJDIR)
$(BINDIR):
	mkdir -p $(BINDIR)

clean:
	rm -f $(OBJDIR)/*   2>/dev/null || true
	rm -f $(BINDIR)/*   2>/dev/null || true
	rm -f $(SRCDIR)/*.o 2>/dev/null || true

rebuild: clean $(EXEC)

$(PCH_OUT): $(PCH_SRC) | $(OBJDIR)
	$(CC) $(CCFLAGS) $(INC) -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(PCH_OUT) | $(OBJDIR)
	$(CC) $(CCFLAGS) $(INC) -include $(PCH_SRC) -c $< -o $@ $(LIBS)