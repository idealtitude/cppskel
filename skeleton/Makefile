# Basic vars & flags
CXX=clang++
CXXFLAGS=-std=c++23 -O0 -W -Wall -Werror -Wextra -Wshadow -pthread -Wno-sign-compare -Wconversion -Wno-unused-function -Wpedantic -pedantic -pedantic-errors -g
LDFLAGS=

# Directories & other
BINNAME={{app}}
BINDIR=bin
SRCDIR=src
OBJDIR=build
SRCS=$(wildcard $(SRCDIR)/*.cpp)
OBJS=$(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))
VERSIONNO=$(shell cat ./VERSION)
PREFIX ?= $(HOME)/.local

BIN=$(BINDIR)/$(BINNAME)-$(VERSIONNO)

.PHONY: all release install uninstall version clean cleanall

all:$(BIN)

release: CXXFLAGS=-std=c++23 -Wall -O2 -DNDEBUG
release: cleanall
release: $(BIN)

install: CXXFLAGS=-std=c++23 -Wall -O2 -DNDEBUG -DINSTALLING
install: cleanall
install: $(BIN)
install:
	@echo "Installing $(BINNAME)-$(VERSIONNO)"
	@echo "Creating configuration directories..."
	@mkdir -p "$(HOME)/.config/$(BINNAME)"
	@mkdir -p "$(PREFIX)/share/$(BINNAME)"
	@mkdir -p "$(PREFIX)/bin"

	@echo "Installing configuration files..."
	@install -D data/user_preferences.conf "$(HOME)/.config/$(BINNAME)/user_preferences.conf"
	@install -D data/$(BINNAME).conf "$(PREFIX)/share/$(BINNAME)/$(BINNAME).conf"
	@install -D data/help.txt "$(PREFIX)/share/$(BINNAME)/help.txt"
	@install -D VERSION "$(PREFIX)/share/$(BINNAME)/version.txt"

	@echo "Installing executable..."
	@install -D bin/$(BINNAME)-$(VERSIONNO) "$(PREFIX)/bin/$(BINNAME)"
	@chmod +x "$(PREFIX)/bin/$(BINNAME)"

	@echo "Installation complete!"
	@echo "$(BINNAME) executable path is $(PREFIX)/bin/$(BINNAME)"

uninstall:
	@echo "Removing installed files and directories..."
	@rm -rf "$(HOME)/.config/$(BINNAME)"
	@rm -rf "$(PREFIX)/share/$(BINNAME)"
	@rm -f "$(PREFIX)/bin/$(BINNAME)" # Maybe be more specific about removing the bin executable
	@echo "Uninstallation complete!"

$(BIN): $(OBJS) $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $@

$(BINDIR):
	@mkdir -p $@

version:
	@echo $(BINNAME) version $(VERSIONNO)

clean:
	$(RM) -r $(OBJDIR)

cleanall: clean
	$(RM) -r $(BINDIR)/*
