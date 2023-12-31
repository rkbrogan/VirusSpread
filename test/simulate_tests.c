#include "simulate_tests.h"

#include "simulate.h"
#include "random.h"
#include "virus.h"

#include "time.h"
#include <stdio.h>
#include <unistd.h>

// To handle unused parameter in unit tests
#define UNUSED(x) (void)(x)

#define TEST(name) { (char*)#name, name, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }

// Test: Simple test
static MunitResult simple_test(const MunitParameter params[], void* data)
{
    UNUSED(params);
    UNUSED(data);

    int arr[5];
    int arr2[5];

    uint32_t seed = munit_rand_uint32();

    // Seed rand
    srand(seed);

    for (int i = 0; i < 5; i++)
    {
        arr[i] = rand();
    }

    // Re-seed rand
    srand(seed);

    for (int i = 0; i < 5; i++)
    {
        arr2[i] = rand();
    }

    // Compare
    munit_assert_memory_equal(sizeof(arr), arr, arr2);

    return MUNIT_OK;
}

// Test: Simulate catch_or_not with population of zero people, trpob = 0.5
static MunitResult catch_or_not_zero_people(const MunitParameter params[], void* data)
{
    // Set up tprob
    double tprob = 0.5;

    // Set up npeople
    int npeople = 0;

    // Set up status of zero people
    int status[npeople];

    // Execute
    int result = catch_or_not(tprob, npeople, status);

    // Assert
    munit_assert_int(result, ==, 0); 

    return MUNIT_OK;
}

// Test: Simulate catch_or_not with population of one positive person, tprob = 0.5
static MunitResult catch_or_not_one_person(const MunitParameter params[], void* data)
{
    // Set up tprob
    double tprob = 0.5;

    // Set up npeople
    int npeople = 1;

    // Set up status of one positive person
    int status[npeople];
    status[0] = 1;

    // Loop until person is infected
    int result = 0;
    while (result == 0)
    {
        result = catch_or_not(tprob, npeople, status);
    }

    // Assert
    munit_assert_int(result, ==, 1);

    return MUNIT_OK;
}

// Test: Simulate catch_or_not with population of one positive person, tprob = 1.0
static MunitResult catch_or_not_one_person_tprob_one(const MunitParameter params[], void* data)
{
    // Set up tprob
    double tprob = 1.0;

    // Set up npeople
    int npeople = 1;

    // Set up status of one positive person
    int status[npeople];
    status[0] = 1;

    int result = is_susceptible;

    // Run catch_or_not    
    result = catch_or_not(tprob, npeople, status);

    // Assert
    munit_assert_int(result, ==, is_infected);

    return MUNIT_OK;
}


// Test: Simulate catch_or_not with population of twenty people with zero infected, tprob = 0.5
static MunitResult catch_or_not_twenty_people_zero_infected(const MunitParameter params[], void* data)
{
    // Set up tprob
    double tprob = 0.5;

    // Set up npeople
    int npeople = 20;

    // Set up status of twenty people with zero infected
    int status[npeople];
    for (int i = 0; i < npeople; i++)
    {
        status[i] = 0;
    }

    // Loop 100 times to ensure no one gets infected
    int result = 0;
    for (int i = 0; i < 100; i++)
    {
        result = catch_or_not(tprob, npeople, status);

        // Assert
        munit_assert_int(result, ==, 0);
    }

    return MUNIT_OK;
}

// Test: Simulate catch_or_not with population of twenty people with half infected, tprob = 0.5
static MunitResult catch_or_not_twenty_people_half_infected(const MunitParameter params[], void* data)
{
    // Set up tprob
    double tprob = 0.5;

    // Set up npeople
    int npeople = 20;

    // Set up status of twenty people with half infected
    int status[npeople];
    for (int i = 0; i < npeople; i++)
    {
        if (i < npeople / 2)
        {
            status[i] = 1;
        }
        else
        {
            status[i] = 0;
        }
    }

    // Loop until person is infected
    int result = 0;
    while (result == 0)
    {
        result = catch_or_not(tprob, npeople, status);
    }

    // Assert
    munit_assert_int(result, ==, 1);

    return MUNIT_OK;
}

// Test: Simulate catch_or_not with population of ten people, tprob = 0.5

// Test: Simulate catch_or_not with population of one hundred people, tprob = 0.5

// Test: Simulate catch_or_not with population of one thousand people, tprob = 0.5

/**************************************************************/
/*************** Full collection of simulate tests ******************/
/**************************************************************/
MunitTest simulate_tests[] = {
    TEST(simple_test),
    TEST(catch_or_not_zero_people),
    TEST(catch_or_not_one_person),
    TEST(catch_or_not_one_person_tprob_one),
    TEST(catch_or_not_twenty_people_zero_infected),
    TEST(catch_or_not_twenty_people_half_infected),
    // TEST_WITH_RESET(write_code_to_file_one_bit, reset_buffer),
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};
