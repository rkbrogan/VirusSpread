/*
    Program tracks the health of 10,000 people for 100 days. Each person's 
    heatlh status is represented by a value in the -3 to 0 range. The
    program uses a 10,000 element array of integers to keep track of the 
    status of each person. 
    
    Program assumes that 100 people are infected on the first day.
*/

#include "random.h"
#include "virus.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define RAND_NUM_PEOPLE 20

/* Function that simulates a random number of encounters between the person and other people.
    Flips virtual coin if person encoutners someone who is infected. Returns status of 
    person. */
int catch_or_not(double tprob, int npeople, int status[])
{
    // Generate random number of people exposed to
    int nexposures = (int)(RAND_NUM_PEOPLE * rand01());

    // Loop through nexposures to determine encounters with people who are infected or not
    for (int i = 0; i < npeople; i++)
    {

    }
    return 0;
}

/* Function that determines if an infected person will die, stay sick, or gets well. 
    If person survives more than ~14 days, person is recovered.*/
int die_or_not(double dprob, int sick_days, int person, int npeople, int status[])
{
    return 0;
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
