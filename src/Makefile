CXX = g++
INSTALL = install
# change CXXTESTGEN and CXXTESTINCLUDEDIR to appropriate directories.
CXXTESTGEN = ../dev/cxxtest/cxxtestgen.pl
CXXTESTGENFLAGS = --abort-on-fail --have-eh
CXXTESTINCLUDEDIR = ../dev/cxxtest

CXXFLAGS = -Wall -I. ${CFLAGS} #-pg # -ggdb3 -DDEBUG
CXXLIBFLAGS = -fPIC -shared


LIBRARY = libmunkres.so

INSTALLDIR = ../build
INSTALL_INCLUDEDIR = $(INSTALLDIR)/include/
INSTALL_LIBDIR = $(INSTALLDIR)/lib/c/

SOURCES = munkres.cpp
OBJECTS := $(patsubst %.cpp,%.o,$(SOURCES))
HEADERS := $(filter-out main.h,$(patsubst %.cpp,%.h,$(SOURCES))) matrix.h matrix.cpp
UNITTESTS = ../tests/singlesolution.h ../tests/validsolution.h

# implementation

.SUFFIXES:      .o .cpp

.cpp.o : $(HEADERS)
	$(CXX) $(CXXFLAGS) $(CXXLIBFLAGS) -c  -o $@ $<

all:	$(LIBRARY)

$(LIBRARY): $(OBJECTS) $(HEADERS)
	$(CXX) -shared -o $(LIBRARY) $(OBJECTS)

install:  $(LIBRARY)
	mkdir -p $(INSTALL_LIBDIR)
	mkdir -p $(INSTALL_INCLUDEDIR)
	$(INSTALL) -m 644 $(LIBRARY) $(INSTALL_LIBDIR)
	$(INSTALL) -m 644 $(HEADERS) $(INSTALL_INCLUDEDIR)

test:	testsuite
	@echo "Running test suite."
	@./testsuite

testsuite: testsuite.cpp $(filter-out main.o,$(OBJECTS))
	$(CXX) -I$(CXXTESTINCLUDEDIR) $(CXXFLAGS) -o $@ $^

testsuite.cpp:	$(UNITTESTS)
	$(CXXTESTGEN) $(CXXTESTGENFLAGS) -o $@ --error-printer $^

clean:
	rm -f $(OBJECTS)
	rm -f $(LIBRARY)
	rm -f testsuite
	rm -f testsuite.cpp

