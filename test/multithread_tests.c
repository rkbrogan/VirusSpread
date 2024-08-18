#include "multithread_tests.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// To handle unused parameter in unit tests
#define UNUSED(x) (void)(x)

// Macro for tests
#define TEST(name) { (char*)#name, name, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }

#define NUM_OF_THREADS 4
#define TOTAL 100000
#define EXPECTED_TOTAL (NUM_OF_THREADS * TOTAL)

pthread_mutex_t grandTotalLock = PTHREAD_MUTEX_INITIALIZER;
bool useLock = true;
long grandTotal = 0;

void* badThreadFunction(void* val)
{
    UNUSED(val);

    grandTotal += TOTAL;
    // Won't work if this sleep() is not used (race conditions)
    sleep(1);

    return NULL;
}

typedef struct threadStruct_t 
{
    int total;
    long* grandTotalPtr;
    pthread_mutex_t* grandTotalMutexPtr;

} threadStruct;

// The function we want to use
void* threadFunction2(void* args)
{
    threadStruct* threadArgs  = ((threadStruct*) args);

    for (int i = 0; i < threadArgs->total; i++)
    {
        if (threadArgs->grandTotalMutexPtr)
        {
            // Lock mutex
            pthread_mutex_lock(threadArgs->grandTotalMutexPtr);

            // Increment grand total
            (*(threadArgs->grandTotalPtr))++;

            // Unlock mutex
            pthread_mutex_unlock(threadArgs->grandTotalMutexPtr);
        }
        else    // For learning purposes
        {
            // Increment grand total (WRONG WAY OF DOING THINGS)
            threadArgs->grandTotalPtr++;
        }
    }
}

// Test with a total of 100 with locking
static MunitResult mThread_program_no_lock(const MunitParameter params[], void* data)
{
    UNUSED(params);
    UNUSED(data);
    
    // int numOfThreads = NUM_OF_THREADS;
    int numOfThreads = 1000;

    pthread_t threadsArr[numOfThreads];

    // Create each thread and run thread function
    for (int i = 0; i < numOfThreads; i++)
    {
        int threadVal = pthread_create(&threadsArr[i], NULL, badThreadFunction, NULL);
        munit_assert_int(threadVal, == , 0);
    }

    // Join/close each thread
    for (int i = 0; i < numOfThreads; i++)
    {
        int threadVal = pthread_join(threadsArr[i], NULL);
        munit_assert_int(threadVal, == , 0);
    }

    // Assert total
    munit_assert_int(grandTotal, ==, EXPECTED_TOTAL);

    return MUNIT_OK;
}

static MunitResult mThread_struct_program_one_hundred_with_lock(const MunitParameter params[], void* data)
{
    UNUSED(params);
    UNUSED(data);
    
    pthread_t threadsArr[NUM_OF_THREADS];

    threadStruct threadArgsArr[NUM_OF_THREADS];

    // Args for threadStructs
    long grandTotal = 0;
    pthread_mutex_t gtLock = PTHREAD_MUTEX_INITIALIZER;

    // Create each thread and run thread function
    for (int i = 0; i < NUM_OF_THREADS; i++)
    {
        // pthread_mutex_t* tempLock = useLock ? &gtLock : NULL;
        threadArgsArr[i].grandTotalMutexPtr = useLock ? &gtLock : NULL;
        threadArgsArr[i].total = TOTAL;
        threadArgsArr[i].grandTotalPtr = &grandTotal;

        int threadVal = pthread_create(&threadsArr[i], NULL, badThreadFunction, (void*) &threadArgsArr[i]);
        // sleep(1);
        munit_assert_int(threadVal, == , 0);
    }

    // Join/close each thread
    for (int i = 0; i < NUM_OF_THREADS; i++)
    {
        int threadVal = pthread_join(threadsArr[i], NULL);
        munit_assert_int(threadVal, == , 0);
    }

    // Assert total
    // munit_assert_int(total, ==, expectedTotal);

    munit_assert_int(grandTotal, ==, EXPECTED_TOTAL);

    return MUNIT_OK;
}

/**************************************************************/
/*************** Full collection of multithread tests ******************/
/**************************************************************/
MunitTest multithread_tests[] = {
    TEST(mThread_program_no_lock),
    TEST(mThread_struct_program_one_hundred_with_lock),
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};