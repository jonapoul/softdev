CXX      = g++ -std=c++11
CXXFLAGS = -c -Wall -g
LD       = $(CXX)
LDFLAGS  = -Wall -g

OBJDIR  := obj
BINDIR  := bin
SRCDIR  := src
INCDIR  := inc
LIBDIR  := lib
LIBDIRS  = $(LIBDIR)/libpf

INC_PF := -I$(LIBDIR)/libpf
LIBS   := $(LIBDIR)/libpf/libPF.a

INC  = -I. -I$(INCDIR) $(INC_PF)
SRC := $(wildcard $(SRCDIR)/*.cpp)
OBJ := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRC))

EXEC = softdev

default: dir $(EXEC)

$(EXEC): $(LIBS) $(OBJ) | dir $(LIBDIRS)
	$(LD) -o $(BINDIR)/$@ $(LDFLAGS) $(OBJ) $(LIBS) -lstdc++fs

dir:
	mkdir -p $(OBJDIR)
	mkdir -p $(BINDIR)
	mkdir -p $(LIBDIR)

$(LIBDIR)/libpf: | dir
	cd $(LIBDIR); git clone https://bitbucket.org/eric_tittley/libpf.git

$(LIBDIR)/libpf/libPF.a: dir $(LIBDIR)/libpf
	cd $(LIBDIR)/libpf; make

clean:
	rm -f $(OBJDIR)/*   2>/dev/null || true
	rm -f $(BINDIR)/*   2>/dev/null || true
	rm -f $(SRCDIR)/*.o 2>/dev/null || true
	cd $(LIBDIR)/libpf; make distclean;

rebuild: clean $(EXEC)

update: | $(LIBDIRS)
	git pull
	cd lib/libpf && git pull

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | dir
	$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@