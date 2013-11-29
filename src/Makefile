CXX = g++
INSTALL = install

CXXFLAGS = -Wall -I. ${CFLAGS} #-pg # -ggdb3 -DDEBUG
CXXLIBFLAGS = -fPIC -shared


LIBRARY = libmunkres.so

INSTALLDIR = ../build
INSTALL_INCLUDEDIR = $(INSTALLDIR)/include/
INSTALL_LIBDIR = $(INSTALLDIR)/lib/c/

SOURCES = munkres.cpp
OBJECTS := $(patsubst %.cpp,%.o,$(SOURCES))
HEADERS := $(filter-out main.h,$(patsubst %.cpp,%.h,$(SOURCES))) matrix.h matrix.cpp
UNITTESTS = ../tests/munkrestest.cpp
LDPATH =
LDADD = -lgcov -lgtest -lgtest_main -lpthread

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

test:	munkrestest
	@echo "Running test suite."
	@./munkrestest

munkrestest: $(UNITTESTS) $(filter-out main.o,$(OBJECTS))
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDPATH) $(LDADD)

clean:
	rm -f $(OBJECTS)
	rm -f $(LIBRARY)
	rm -f munkrestest

