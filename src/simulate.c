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
#include <stdlib.h>
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
    // Unsure if this is needed?
    (void) npeople;

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

// int _main (int argc, char* argv[])
// {
//     const int npeople=1e+4;
//     int status[npeople];
//     int newstatus[npeople];
//     int day,person;
//     double vprob; // Vaccination probability.
//     double tprob; // Transmission probability
//     double dprob = 0.015; // Death probability per day
//     int ndays = 100;
//     int initial_infections = 0.01*npeople;
//     int sick_days = 14;
//     FILE *output;

//     // Insert the rest of the program here
    
//     // Check number of command line arguments
//     if (argc != 3)
//     {
//         printf("Not enough command line arguments.");
//         return -1;
//     }

//     // Set values from program arguments
//     vprob = atof(argv[1]);
//     tprob = atof(argv[2]);
//     // TODO: Error check vprob and tprob

//     output =  fopen(argv[3], "w");
//     // TODO: Error check output

//     // Calculate number of vaccinated people
//     int nvaccinated  = (int)(vprob * npeople);

//     // Set initial status of each person
//     initialize_status(npeople, initial_infections, nvaccinated, status);

//     // Simulate 100 days
//     for (day = 0; day < 100; day++)
//     {
//         // Simulate through population
//         for (person = 0; person < npeople; person++)
//         {
//             // Get status of person
//             int personStatus = status[person];

//             // Update status of person for next day
//             // If person is susceptible, check if they get virus
//             // Else if person is sick, see if they die
//             // Otherwise person stays same status
//             if (personStatus == is_susceptible)
//             {
//                 newstatus[person] = catch_or_not(tprob, npeople, status);
//             }
//             else if (personStatus >= is_infected)
//             {
//                 newstatus[person] = die_or_not(dprob, sick_days, person, npeople, status);
//             }
//             else
//             {
//                 newstatus[person] = personStatus;
//             }
//         }

//         // Copy newstatus to status
//         update_status(npeople, status, newstatus);

//         // Print daily stats
//         printf("\n");
//         fprintf(output, "%d %d %d %d %d %d\n", day, nsusceptible, nrecovered, nvaccinated, ninfected, ndead);
//     }

//     // printf ( "Population: %d\n", npeople );
//     // printf ( "Vaccination Probability: %lf\n", vprob );
//     // printf ( "Transmission Probability: %lf\n", tprob );
//     // printf ( "Initial Infections: %d\n", initial_infections );
//     // printf ( "Simulation Period: %d days\n", ndays );
//     // printf ( "Number of Recovered: %d\n", nrecovered );
//     // printf ( "Number of Dead: %d\n", ndead );
//     // printf ( "Case Fatality Rate: %lf\n", (double)ndead/(nrecovered+ndead) );

//     return 0;
// }
