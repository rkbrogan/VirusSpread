/*
    Program tracks the health of 10,000 people for 100 days. Each person's 
    heatlh status is represented by a value in the -3 to 0 range. The
    program uses a 10,000 element array of integers to keep track of the 
    status of each person. 
    
    Program assumes that 100 people are infected on the first day.
*/

#include "simulate.h"

#include "random.h"
#include "virus.h"

#include <stdio.h>
#include <math.h>
#include <time.h>

#define RAND_NUM_PEOPLE 20
#define POPULATION_NANTUCKET 10000
#define TRACKING_LENGTH 100

/* Function that simulates a random number of encounters between the person and other people.
    Flips virtual coin if person encoutners someone who is infected. Returns status of 
    person. */
int catch_or_not(double tprob, int npeople, int status[])
{
    int result = is_susceptible;

    // Generate random number of people exposed to
    int nexposures = (int)(RAND_NUM_PEOPLE * rand01());

    // Loop through nexposures to determine encounters with people who are infected or not
    for (int i = 0; i < nexposures; i++)
    {
        // Pick random other person from list
        int otherPerson = (int)(rand01() * npeople);

        // Check if other person is infected
        if (status[otherPerson] >= is_infected)
        {
            // Flip virtual coin to determine if person gets infected
            if (rand01() < tprob)
            {
                result = is_infected;
                break;
            }
        }
    }
    
    return result;
}

// Function wrapper for testing catch_or_not()
int catch_or_not_wrapper(double tprob, int npeople, int status[])
{
    srand(0);

    int result = catch_or_not(tprob, npeople, status);
    
    return result;
}

/* Function that determines if an infected person will die, stay sick, or gets well. 
    If person survives more than ~14 days, person is recovered.*/
int die_or_not(double dprob, int sick_days, int person, int npeople, int status[])
{
    int result = status[person];

    // Get number between 0 and 1
    double randNum = rand01();

    // Check if less than dprob
    if (randNum < dprob)
    {
        // Person has died
        result = is_dead;
    }
    else
    {
        // See if person recovers or remains sick
        if (result > (sick_days + 3.0 * normal()))
        {
            // Person is recovered
            result = is_recovered;
        }
        else
        {
            // Person stays infected for another day.
            result++;
        }
    }
    
    return result;
}

int _main (int argc, char* argv[])
{
    const int npeople=1e+4;
    int status[npeople];
    int newstatus[npeople];
    int day,person;
    double vprob; // Vaccination probability.
    double tprob; // Transmission probability
    double dprob = 0.015; // Death probability per day
    int ndays = 100;
    int initial_infections = 0.01*npeople;
    int sick_days = 14;
    FILE *output;

    // Insert the rest of the program here

    // printf ( "Population: %d\n", npeople );
    // printf ( "Vaccination Probability: %lf\n", vprob );
    // printf ( "Transmission Probability: %lf\n", tprob );
    // printf ( "Initial Infections: %d\n", initial_infections );
    // printf ( "Simulation Period: %d days\n", ndays );
    // printf ( "Number of Recovered: %d\n", nrecovered );
    // printf ( "Number of Dead: %d\n", ndead );
    // printf ( "Case Fatality Rate: %lf\n", (double)ndead/(nrecovered+ndead) );
}
