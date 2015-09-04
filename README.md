munkres-cpp
===========

[![build](https://travis-ci.org/Gluttton/munkres-cpp.svg?branch=master)](https://travis-ci.org/Gluttton/munkres-cpp)
[![codecov.io](http://codecov.io/github/Gluttton/munkres-cpp/coverage.svg?branch=master)](http://codecov.io/github/Gluttton/munkres-cpp?branch=master)


An implementation of the Kuhn–Munkres algorithm.



License
-------

Copyright (c) 2007-2013 John Weaver and contributors.  
Licensed under the GPLv2. See the file COPYING for details.



Usage
-----

```$ git clone https://github.com/saebyn/munkres-cpp.git```  

Requires:  
 - C++ compiler with C++11 support.  

To usage code it's just required add ```src/munrkes.cpp``` file into your project.  



Example
-------

TBD.



Development
-----------

Requires:  
 - GCC (tested on 4.6.3, 4.8);  
 - GNU Make;  
 - CMake )2.8.12);  
 - the test suite requires the [Google C++ Test Framework](http://code.google.com/p/googletest/);  
 - microbenchmaring requires Benchmark, Celero, Hayai, gprof;  
 - code coverage requires gcov, lcov;  
 - static code analyzis required cppcheck.  

```$ git clone https://github.com/saebyn/munkres-cpp.git```  
```$ cd munkres-cpp```  
```$ mkdir build && cd build```  
```$ cmake -DCMAKE_BUILD_TYPE={Debug, Release, etc} ..```  
```$ make```  
etc...  

Lunch unit tests:  
```$ mkdir build && cd build```  
```$ cmake -DCMAKE_BUILD_TYPE=Debug ..```  
```$ make```  
```$ tests/munkrestest```  

Lunck code coverage analyze:  
```$ <build and lunch unit tests>```  
```$ make coverage```  
```$ firefox coverage/index.html &```  

Lunch memory profiler:  
```$ mkdir build && cd build```  
```$ cmake -DCMAKE_BUILD_TYPE=Debug ..```  
```$ make```  
```$ valgrind tests/munkrestest```  

Lunch microbenchmark tests:  
```$ mkdir build && cd build```  
```$ cmake -DCMAKE_BUILD_TYPE=Release ..```  
```$ make```  
```$ benchmarks/tools/generator/matrixgenerator.bin {dim_1 dim_2 ... dim_n}```  
```$ benchmarks/tests/munkresbenchmark_celero.bin```  
```$ benchmarks/tests/munkresbenchmark_google.bin```  
```$ benchmarks/tests/munkresbenchmark_hayai.bin```  
```$ benchmarks/tests/munkresbenchmark_rdtsc.bin```  

Lunch static code analyze tests:  
```$ make cppcheck```  

Lunch performance analyze:  
```$ mkdir build && cd build```  
```$ cmake -DCMAKE_BUILD_TYPE=Release ..```  
```$ make```  
```$ benchmarks/tools/generator/matrixgenerator.bin {dim_1 dim_2 ... dim_n}```  
```$ benchmarks/tests/munkresbenchmark_gprof.bin```  
```$ gprof benchmarks/tests/munkresbenchmark_gprof.bin gmon.out -p -b```  

Lunch code formatter:  
TBD  


Bug reporting and work to be done
---------------------------------

Check the [issues list at GitHub](https://github.com/saebyn/munkres-cpp/issues?state=open).

