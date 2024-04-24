#include "random.h"
#include "simulate.h"
#include "virus.h" 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>


int main (int argc, char* argv[])
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
    // For Analyze
    double sum = 0;
    double sum2 = 0;
    int trial;
    int ntrials; 

    FILE *output;

    // Insert the rest of the program here

    // TODO: run simulate and analyze from here via command line arguments
    // TODO: decide how the format of output
    
    // Check number of command line arguments
    if (argc < 4)
    {
        printf("Not enough command line arguments.\n");
        printf("%d arguments given", argc);
        return -1;
    }

    // Set values from program arguments
    vprob = atof(argv[1]);
    tprob = atof(argv[2]);
    // TODO: Error check vprob and tprob

    output =  fopen(argv[3], "w");
    // TODO: Error check output

    // if 4th argument is "simulate", set ntrials to 1
    if (argc == 5)
    {
        if (strcmp(argv[4], "simulate") == 0)
        {
            ntrials = 1;
        }
        // else "analyze"
        else if (strcmp(argv[4], "analyze") == 0)
        {
            ntrials = 1000;
        }
        else
        {
            printf("Invalid argument given");
            return -1;
        }
    }
    else
    {
        ntrials = 100;
    }

    // Calculate number of vaccinated people
    int nvaccinated  = (int)(vprob * npeople);

    for (trial = 0; trial < ntrials; trial++)
    {
        int realTrialNumber = trial+1;

        // Print message every 10 trials
        if (realTrialNumber % 10 == 0)
        {
            printf("---- Processing trial %d ----\n", realTrialNumber);
        }

        // Set initial status of each person
        initialize_status(npeople, initial_infections, nvaccinated, status);

        // Simulate 100 days
        for (day = 0; day < ndays; day++)
        {
            // Simulate through population
            for (person = 0; person < npeople; person++)
            {
                // Get status of person
                int personStatus = status[person];

                // Update status of person for next day
                // If person is susceptible, check if they get virus
                // Else if person is sick, see if they die
                // Otherwise person stays same status
                if (personStatus == is_susceptible)
                {
                    newstatus[person] = catch_or_not(tprob, npeople, status);
                }
                else if (personStatus >= is_infected)
                {
                    newstatus[person] = die_or_not(dprob, sick_days, person, npeople, status);
                }
                else
                {
                    newstatus[person] = personStatus;
                }
            }

            // Copy newstatus to status
            update_status(npeople, status, newstatus);

            // If simulate, print daily stats
            if (ntrials == 1)
            {
                // Print daily stats
                printf("\n");
                fprintf(output, "%d %d %d %d %d %d\n", day, nsusceptible, nrecovered, nvaccinated, ninfected, ndead);
            }
            else
            {
                sum += ndead;
                sum2 += ndead*ndead;

                fprintf ( output, "%d %d %d %d %d %d\n", trial, nsusceptible, nrecovered, nvaccinated, ninfected, ndead );
            }
        } 
        
    }

    printf ( "Population: %d\n", npeople );
    printf ( "Vaccination Probability: %lf\n", vprob );
    printf ( "Transmission Probability: %lf\n", tprob );
    printf ( "Initial Infections: %d\n", initial_infections );
    printf ( "Simulation Period: %d days\n", ndays );
    if (ntrials == 1)
    {
        printf( "Number of trials: %d\n", ntrials );
        printf( "Average number of deaths: %lf\n", sum/ntrials );
        printf( "Standard deviation of deaths: %lf\n", sqrt((sum2 - sum*sum/ntrials)/(ntrials-1)) );
    }
    else
    {
        printf ( "Number of Recovered: %d\n", nrecovered );
        printf ( "Number of Dead: %d\n", ndead );
        printf ( "Case Fatality Rate: %lf\n", (double)ndead/(nrecovered+ndead) );
    }

    return 0;
}
