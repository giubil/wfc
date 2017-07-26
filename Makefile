CXXFLAGS := --std=c++14 -Wall -Wno-sign-compare -O2 -g -DNDEBUG
CPPFLAGS := -I libs -I libs/emilib
LDLIBS   := -lstdc++ -lpthread -ldl

BIN = wfc
DISTDIR = build
OUTPUTDIR = output
SRCDIR  = src
SRCFILES = $(wildcard $(SRCDIR)/*.cpp)
INCDIR = inc
INCFILES = $(wildcard $(INCDIR)/*h)
OBJFILES = $(patsubst $(SRCDIR)/%.cpp, $(DISTDIR)/%.o, $(SRCFILES))
RM = rm -rf
MKDIR = mkdir -p
CXXFLAGS += -I./$(INCDIR)


all: setup $(BIN)

$(BIN): $(OBJFILES)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $^ $(LDLIBS) -o $(BIN)

$(DISTDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

.PHONY: run clean distclean fclean re

setup: $(DISTDIR) $(OUTPUTDIR)
	git submodule update --init --recursive

$(DISTDIR):
	$(MKDIR) $(DISTDIR)

$(OUTPUTDIR):
	$(MKDIR) $(OUTPUTDIR)

run: all
	./$(BIN)

clean:
	$(RM) $(OBJFILES) $(DISTDIR)

fclean: clean
	$(RM) $(BIN)

re: fclean all
