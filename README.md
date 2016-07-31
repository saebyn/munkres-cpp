munkres-cpp
===========

[![build status](https://gitlab.com/Gluttton/munkres-cpp/badges/devel/build.svg)](https://gitlab.com/Gluttton/munkres-cpp/commits/devel)
[![codecov](https://codecov.io/gl/Gluttton/munkres-cpp/branch/devel/graph/badge.svg)](https://codecov.io/gl/Gluttton/munkres-cpp)


An implementation of the Kuhn–Munkres algorithm.



License
-------

Copyright (c) 2007-2013 John Weaver and contributors.  
Licensed under the GPLv2. See the file COPYING for details.



Requires
--------

For using:  
 - C++ compiler with C++11 support.  


For development:  
 - [GCC](https://gcc.gnu.org/) (tested on 4.6.3, 4.8);  
 - [GNU Make](https://www.gnu.org/software/make/);  
 - [CMake](http://www.cmake.org/) (2.8.12);  
 - the test suite requires the [Google C++ Test Framework](http://code.google.com/p/googletest/);  
 - microbenchmaring requires [Benchmark](https://github.com/google/benchmark), [Celero](https://github.com/DigitalInBlue/Celero), [Hayai](https://github.com/nickbruun/hayai) and [gprof](http://www.gnu.org/software/binutils/);  
 - code coverage requires [gcov](https://gcc.gnu.org/onlinedocs/gcc/Gcov.html) and lcov;  
 - static code analyzis required [cppcheck](https://github.com/danmar/cppcheck).  



Portability
-----------

The project is developing under GNU/Linux OS with gcc compiler and usualy not tested under other OS and compilers.
But in the project not used OS or compiler specific features (types, attributes, etc) so it's expected that the project will be normally work under other platforms.



Usage
-----

To use the project the following steps are required:  
  - download: ```$ git clone https://github.com/saebyn/munkres-cpp.git && cd munkres-cpp```  
  - build: ```$ mkdir build && cd build $$ cmake .. && make```  
  - install: ``` $ make install```  



Example
-------

TBD



Development
-----------

For development purpose in the project implemented a variety of build targets.
All of them help to continuously check correctness of algorithm implementation, performance, memory management, etc.
To configure project in development mode ```-DMUNKRESCPP_DEVEL_MODE=ON``` option must be passed to CMake.
Also for debug purpose defined macro which in primitive way provides basic concepts
of [Design By Contract](https://en.wikipedia.org/wiki/Design_by_contract). By default the macro is disabled and
assertions are not checked. The macro can be enabled in one of modes: if assertion is failed only printing debug message (1),
or throwing exception (2). To configure the mode ```-DDBC_MODE=X``` option must be passed to CMake.

Launch of unit tests.
The project contains unit tests to build and launch it performs the following steps:
```
$ git clone https://github.com/saebyn/munkres-cpp.git
$ cd munkres-cpp
$ mkdir build && cd build
$ cmake -DCMAKE_BUILD_TYPE=Debug -DMUNKRESCPP_DEVEL_MODE=ON ..
$ make tests
$ tests/munkrestest
```


Lunch code coverage analyze.
To get correct report unit tests must be compiled in debug mode.
```
$ <build and lunch unit tests>
$ make coverage
$ firefox coverage/index.html &
```


Lunch memory profiler.
As far unit tests call all functions which implement algorithm this is appropriate way to check memory management by using valgrind during performing unit tests.
```
$ <build unit tests>
$ valgrind tests/munkrestest
```


Lunch microbenchmarks.
Buildning microbenchmarks:
```
$ git clone https://github.com/saebyn/munkres-cpp.git
$ cd munkres-cpp
$ mkdir build && cd build
$ cmake -DCMAKE_BUILD_TYPE=Release -DMUNKRESCPP_DEVEL_MODE=ON ..
$ make benchmarks
```
To get comparable results it's required to generate data set wich will be used for all benchmarks:
```
$ benchmarks/tools/generator/matrixgenerator.bin {dim_1 dim_2 ... dim_n}
```
Where every ```dim_x``` parameter generate square matrix dith ```dim_x``` dimension.
To launch microbenchmark performs any following command:
```
$ benchmarks/tests/munkresbenchmark_celero.bin
$ benchmarks/tests/munkresbenchmark_google.bin
$ benchmarks/tests/munkresbenchmark_hayai.bin
$ benchmarks/tests/munkresbenchmark_rdtsc.bin
```


Lunch performance analyze.
```
$ <build microbenchmarks and generate data set>
$ benchmarks/tests/munkresbenchmark_gprof.bin
$ gprof benchmarks/tests/munkresbenchmark_gprof.bin gmon.out -p -b
```


Lunch static code analyze.
```
$ make cppcheck
```


Lunch code formatter.
Code formatter is used to convert style of each contributor to common style and make code easier to read.  
In the project [Uncrustify](http://uncrustify.sourceforge.net) is used as code formatter.  
Modified code before commit should be formatted using Uncrustify.  
```
$ make beauty
```


Bug reporting and work to be done
---------------------------------

Check the [issues list at GitHub](https://github.com/saebyn/munkres-cpp/issues?state=open).
