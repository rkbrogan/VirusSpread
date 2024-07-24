#include <stdlib.h>

#include "munit.h"

#include "simulate_tests.h"
#include "threads_tests.h"
#include "multithread_tests.h"

#define TEST(name) { (char*)#name, name, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }

// To handle unused parameter in unit tests
#define UNUSED(x) (void)(x)

// Test 1: Initialize a node with a symbol and frequency of 0
static MunitResult unit_test(const MunitParameter params[], void* data)
{
    UNUSED(params);
    UNUSED(data);

    return MUNIT_OK;
}

// List of tests
MunitTest tests_array[] =
{
    TEST(unit_test),
    {NULL, NULL, NULL, NULL, 0, NULL}
};

/* Now we'll actually declare the test suite.  You could do this in
 * the main function, or on the heap, or whatever you want. */
static const MunitSuite test_suite = {
	/* This string will be prepended to all test names in this suite;
	 * for example, "/example/rand" will become "/�nit/example/rand".
	 * Note that, while it doesn't really matter for the top-level
	 * suite, NULL signal the end of an array of tests; you should use
	 * an empty string ("") instead. */
	(char*)"suite/",
	/* The first parameter is the array of test suites. */
	// simulate_tests,
	// threads_tests,
	multithread_tests,
	/* In addition to containing test cases, suites can contain other
	 * test suites.  This isn't necessary in this example, but it can be
	 * a great help to projects with lots of tests by making it easier
	 * to spread the tests across many files.  This is where you would
	 * put "other_suites" (which is commented out above). */
	NULL,
	/* An interesting feature of �nit is that it supports automatically
	 * running multiple iterations of the tests.  This is usually only
	 * interesting if you make use of the PRNG to randomize your tests
	 * cases a bit, or if you are doing performance testing and want to
	 * average multiple runs.  0 is an alias for 1. */
	1,
	/* Just like MUNIT_TEST_OPTION_NONE, you can provide
	 * MUNIT_SUITE_OPTION_NONE or 0 to use the default settings. */
	MUNIT_SUITE_OPTION_NONE
};


int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  /* Finally, we'll actually run our test suite!  That second argument
   * is the user_data parameter which will be passed either to the
   * test or (if provided) the fixture setup function. */
  return munit_suite_main(&test_suite, (void*) "µnit", argc, argv);
}
