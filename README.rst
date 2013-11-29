
An implementation of the Kuhn–Munkres algorithm


Usage
-----

A sample Makefile is supplied.
Run "make test" to run the testing framework (you must change the path to
cxxtest [http://cxxtest.sourceforge.net/] in the Makefile in order to use this).

License
-------

Copyright (c) 2007 John Weaver
Licensed under the GPLv2. See the file COPYING for details.


TODOs
-----

Here are some things that could be done that might be useful:


* Replace cxxtest with http://code.google.com/p/googletest/

* Code cleanup and add more comments

  - Extract methods / functions out of the longer steps

* Enforce class invariants when DEBUG def'd?

* Support other matrix data type classes from other libs (boost)?

  - Might make it easier for others to integrate this code into their projects.
