quarto
======

A Quarto solver

Directory Structure
===================

* bin/ -- Built executables are put here
* build/ -- Run the Makefile here, object files live here
* src/ -- Source
* tests/ -- Tests

Testing
=======

From the build directory, just `make test`

To add a new test, add a file in tests, declare test functions in test.h and call the functions from test.c.  Finally, update the TEST_OBJS variable in the Makefile.
