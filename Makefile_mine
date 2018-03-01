CXX      = g++ -std=c++11
CXXFLAGS = -c -Wall
LDFLAGS  = -Wall

# ROOTDIR := $(shell pwd)
OBJDIR  := obj
BINDIR  := bin
SRCDIR  := src
INCDIR  := inc
DATDIR  := data
LIBDIRS = lib/libpf \
          lib/matplotlib-cpp

INC_MPL := -Ilib/matplotlib-cpp -I/usr/include/python2.7
LIB_MPL := -lpython2.7

INC_LIBPF := -Ilib/libpf
LIB_LIBPF := lib/libpf/libPF.a

LIBS = $(LIB_MPL) \
       $(LIB_LIBPF)

INC  = -I$(INCDIR) \
         $(INC_MPL) \
         $(INC_LIBPF)

SRC := $(wildcard $(SRCDIR)/*.cpp)
OBJ := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRC))

PCH_SRC = $(INCDIR)/pch.h
PCH_OUT = $(OBJDIR)/pch.h.gch

EXEC = main

default: dir $(EXEC)

$(EXEC): $(LIBDIRS) $(OBJ) | dir
	$(CXX) -o $(BINDIR)/$@ $(LDFLAGS) $(OBJ) $(LIBS)

dir:
	mkdir -p $(OBJDIR)
	mkdir -p $(BINDIR)
	mkdir -p $(DATDIR)
	mkdir -p lib

lib/libpf:
	cd lib; git clone git@bitbucket.org:eric_tittley/libpf.git; cd libpf; make

lib/matplotlib-cpp:
	cd lib; git clone https://github.com/lava/matplotlib-cpp.git; cd matplotlib-cpp; make

clean:
	rm -f  $(OBJDIR)/*   2>/dev/null || true
	rm -f  $(BINDIR)/*   2>/dev/null || true
	rm -f  $(SRCDIR)/*.o 2>/dev/null || true

rebuild: clean $(EXEC)

update: | $(LIBDIRS)
	git pull
	cd lib/matplotlib-cpp && git pull
	cd lib/libpf && git pull

$(PCH_OUT): $(PCH_SRC) | dir
	$(CXX) $(CXXFLAGS) $(INC) $(MPLINC) $(MPLLIB) -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(PCH_OUT) | dir
	$(CXX) $(CXXFLAGS) $(INC) -include $(PCH_SRC) -c $< -o $@