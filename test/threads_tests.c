#include "simulate_tests.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// To handle unused parameter in unit tests
#define UNUSED(x) (void)(x)

// Macro for tests
#define TEST(name) { (char*)#name, name, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }

void* print_message_function(void* ptr)
{
    char* message;
    message = (char*) ptr;
    printf("%s", message);

    message[0] = '*';

    return NULL;
}

// int* add_ten_function(void* ptr)
// {
//     int* ptrInt = (int*) ptr;

//     int newVal = ptrInt + 10;

//     ptrInt = newVal;
// }

// Test: Create a single thread
static MunitResult create_single_thread(const MunitParameter params[], void* data)
{
    UNUSED(params);
    UNUSED(data);

    pthread_t thread;
    char message[] = "Thread 1";

    int threadVal = pthread_create(&thread, NULL, print_message_function, (void*) message);
    munit_assert_int(threadVal, ==, 0);

    // Wait for thread to complete
    threadVal = pthread_join(thread, NULL);
    munit_assert_int(threadVal, ==, 0);

    return MUNIT_OK;
}

// Test: Create a thread that writes to a buffer
static MunitResult thread_write_to_buffer(const MunitParameter params[], void* data)
{
    UNUSED(params);
    UNUSED(data);

    pthread_t thread;
    char message[] = "Thread 1";

    // Set up a buffer
    // char buffer[256];
    // memset(buffer, 0, sizeof(buffer));

    int threadVal = pthread_create(&thread, NULL, print_message_function, (void*) message);
    munit_assert_int(threadVal, ==, 0);

    // Wait for thread to complete
    threadVal = pthread_join(thread, NULL);
    munit_assert_int(threadVal, ==, 0);

    munit_assert_char(message[0], ==, '*');

    // Check the buffer for the expected message
    // munit_assert_string_equal(buffer, "Thread 1");

    return MUNIT_OK;
}


/**************************************************************/
/*************** Full collection of simulate tests ******************/
/**************************************************************/
MunitTest threads_tests[] = {
    TEST(create_single_thread),
    TEST(thread_write_to_buffer),
    // TEST_WITH_RESET(write_code_to_file_one_bit, reset_buffer),
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};