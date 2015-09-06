munkres-cpp
===========

[![build](https://travis-ci.org/saebyn/munkres-cpp.svg?branch=master)](https://travis-ci.org/saebyn/munkres-cpp)
[![codecov.io](http://codecov.io/github/saebyn/munkres-cpp/coverage.svg?branch=master)](http://codecov.io/github/saebyn/munkres-cpp?branch=master)


An implementation of the Kuhn–Munkres algorithm.



License
-------

Copyright (c) 2007-2013 John Weaver and contributors.  
Licensed under the GPLv2. See the file COPYING for details.



Requirements
------------

For use:  
 - C++ compiler with C++11 support.  


For development:  
 - [GCC](https://gcc.gnu.org/) (tested on 4.6.3, 4.8);  
 - [GNU Make](https://www.gnu.org/software/make/);  
 - [CMake](http://www.cmake.org/) (2.8.12);  
 - the test suite requires the [Google C++ Test Framework](http://code.google.com/p/googletest/);  
 - microbenchmarking requires [Benchmark](https://github.com/google/benchmark), [Celero](https://github.com/DigitalInBlue/Celero), [Hayai](https://github.com/nickbruun/hayai) and [gprof](http://www.gnu.org/software/binutils/);  
 - code coverage requires [gcov](https://gcc.gnu.org/onlinedocs/gcc/Gcov.html) and lcov;  
 - static code analyzer requires [cppcheck](https://github.com/danmar/cppcheck).  



Portability
-----------

The project is developed under the GNU/Linux OS with the gcc compiler and usually not tested under other OSs and compilers.
But the project does not use OS or compiler specific features (types, attributes, etc) so it's expected that the project will be normally work under other platforms.



Usage
-----

These steps are the easiest way to get started:
  - download: ```$ git clone https://github.com/saebyn/munkres-cpp.git && cd munkres-cpp```  
  - build: ```$ mkdir build && cd build $$ cmake .. && make```  
  - install: ``` $ make install```  



Example
-------

TBD



Development
-----------

For development purpose, the project implements a variety of build targets.
All of them help to continuously check correctness of algorithm implementation, performance, memory management, etc.
Pass the```-DMUNKRESCPP_DEVEL_MODE=ON``` option to CMake to enable development mode.

# Running unit tests:

Build and execute the test suite with these commands:
```
$ git clone https://github.com/saebyn/munkres-cpp.git
$ cd munkres-cpp
$ mkdir build && cd build
$ cmake -DCMAKE_BUILD_TYPE=Debug -DMUNKRESCPP_DEVEL_MODE=ON ..
$ make tests
$ tests/munkrestest
```


# Running code coverage analyzer:

You must compile unit tests in debug mode to get a correct code coverage report.
```
$ <build and Launch unit tests>
$ make coverage
$ firefox coverage/index.html &
```


# Running the memory profiler:

Since the unit tests call all functions which implement the algorithm, using valgrind on the unit test runner is an appropriate way to check memory management.
```
$ <build unit tests>
$ valgrind tests/munkrestest
```


# Running the microbenchmarks:

First, build them:
```
$ git clone https://github.com/saebyn/munkres-cpp.git
$ cd munkres-cpp
$ mkdir build && cd build
$ cmake -DCMAKE_BUILD_TYPE=Release -DMUNKRESCPP_DEVEL_MODE=ON ..
$ make benchmarks
```

To get comparable results it's required to generate the data set wich will be used for all benchmarks:
```
$ benchmarks/tools/generator/matrixgenerator.bin {dim_1 dim_2 ... dim_n}
```
Where every ```dim_x``` parameter generates a square matrix with ```dim_x``` dimension.
To launch microbenchmarks, perform the following commands:
```
$ benchmarks/tests/munkresbenchmark_celero.bin
$ benchmarks/tests/munkresbenchmark_google.bin
$ benchmarks/tests/munkresbenchmark_hayai.bin
$ benchmarks/tests/munkresbenchmark_rdtsc.bin
```


# Getting performance profiling:

```
$ <build microbenchmarks and generate data set>
$ benchmarks/tests/munkresbenchmark_gprof.bin
$ gprof benchmarks/tests/munkresbenchmark_gprof.bin gmon.out -p -b
```


# Running the static code analyzer:

```
$ make cppcheck
```


# Running the code formatter:

TBD



Bug reporting and work to be done
---------------------------------

Check the [issues list at GitHub](https://github.com/saebyn/munkres-cpp/issues?state=open).
