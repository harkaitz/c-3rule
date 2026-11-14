.SUFFIXES:
.PHONY: all clean install check

PROJECT    =c-3rule
VERSION    =1.0.0
CC         =$(TARGET_PREFIX)cc
CFLAGS     =-Wall -g3 -std=c99
PREFIX     =/usr/local
TOOLCHAINS =noarch
BUILDDIR  ?=.build
EXE        =$(HOMEDRIVE:C:=.exe)
DESTDIR    =$(HOMEDRIVE)
PROGS      =$(BUILDDIR)/3rule$(EXE)

all: $(PROGS)
clean:
	rm -f $(PROGS)
install:
	install -d $(DESTDIR)$(PREFIX)/bin
	install -m755 $(PROGS) $(DESTDIR)$(PREFIX)/bin
check: $(PROGS)
	test @25 = @$$($(BUILDDIR)/3rule$(EXE) 100-50 50-X)
	@echo SUCCESS

$(BUILDDIR)/3rule$(EXE): 3rule.c
	@mkdir -p $(BUILDDIR)
	$(CC) -o $@ 3rule.c $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LIBS)

## -- BLOCK:license --
install: install-license
install-license: README.md COPYING
	install -d $(DESTDIR)$(PREFIX)/share/doc/$(PROJECT)
	install -c -m 644 README.md COPYING $(DESTDIR)$(PREFIX)/share/doc/$(PROJECT)
## -- BLOCK:license --
