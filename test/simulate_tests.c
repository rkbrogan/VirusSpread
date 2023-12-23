#include "simulate_tests.h"

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
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    // Re-seed rand
    srand(seed);

    for (int i = 0; i < 5; i++)
    {
        arr2[i] = rand();
        printf("arr2[%d] = %d\n", i, arr2[i]);
    }

    // Compare
    munit_assert_memory_equal(sizeof(arr), arr, arr2);

    return MUNIT_OK;
}

/**************************************************************/
/*************** Full collection of simulate tests ******************/
/**************************************************************/
MunitTest simulate_tests[] = {
    TEST(simple_test),
    // TEST_WITH_RESET(write_code_to_file_one_bit, reset_buffer),
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};
