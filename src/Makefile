CXX = g++
INSTALL = install

CXXFLAGS = -Wall -I. ${CFLAGS} -std=c++0x #-pg # -ggdb3 -DDEBUG
CXXLIBFLAGS = -fPIC -shared


LIBRARY = libmunkres.so

INSTALLDIR = ../build
DIST_INCLUDEDIR = $(INSTALLDIR)/include/
DIST_LIBDIR = $(INSTALLDIR)/lib/

SOURCES = munkres.cpp
OBJECTS := $(patsubst %.cpp,%.o,$(SOURCES))
HEADERS := $(filter-out main.h,$(patsubst %.cpp,%.h,$(SOURCES))) matrix.h matrix.cpp
UNITTESTS = ../tests/munkrestest.cpp ../tests/matrixtest.cpp ../tests/adapters/raw_2d_arraytest.cpp ../tests/adapters/std_2d_arraytest.cpp ../tests/adapters/boost_matrixtest.cpp
LDPATH =
LDADD = -lgcov -lgtest -lgtest_main -lpthread

# implementation

.SUFFIXES:      .o .cpp

.cpp.o : $(HEADERS)
	$(CXX) $(CXXFLAGS) $(CXXLIBFLAGS) -c  -o $@ $<

all:	$(LIBRARY)

$(LIBRARY): $(OBJECTS) $(HEADERS)
	$(CXX) -shared -o $(LIBRARY) $(OBJECTS)

dist:  $(LIBRARY)
	mkdir -p $(DIST_LIBDIR)
	mkdir -p $(DIST_INCLUDEDIR)
	$(INSTALL) -m 644 $(LIBRARY) $(DIST_LIBDIR)
	$(INSTALL) -m 644 $(HEADERS) $(DIST_INCLUDEDIR)

test:	munkrestest
	@echo "Running test suite."
	@./munkrestest

munkrestest: $(UNITTESTS) $(filter-out main.o,$(OBJECTS))
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDPATH) $(LDADD)

clean:
	rm -f $(OBJECTS)
	rm -f $(LIBRARY)
	rm -f munkrestest

