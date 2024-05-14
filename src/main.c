#include "random.h"
#include "simulate.h"
#include "virus.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    // TODO: Possibly define the constants in the command line arguments
    const int npeople = 1e+4;
    int status[npeople];
    int newstatus[npeople];
    int day, person;
    double vprob;         // Vaccination probability.
    double tprob;         // Transmission probability
    double dprob = 0.015; // Death probability per day
    int ndays = 100;
    int initial_infections = 0.01 * npeople;
    int sick_days = 14;
    // For Analyze
    double sumDead = 0;
    double sumDeadSquared = 0;
    double sumRecovered = 0;
    int trial;
    int ntrials;

    FILE *output;

    // TODO: decide how the format of output

    // TODO: Change this to capture the number of trials from the command line instead of program name.
    // Check number of command line arguments
    // if (argc < 4)
    // {
    //     printf("Not enough command line arguments.\n");
    //     printf("%d arguments given", argc);
    //     return -1;
    // }

    // // Set values from program arguments
    // vprob = atof(argv[1]);
    // tprob = atof(argv[2]);
    // // TODO: Error check vprob and tprob

    // output =  fopen(argv[3], "w");

    // if 4th argument is "simulate", set ntrials to 1
    // if (argc == 5)
    // {
    //     if (strcmp(argv[4], "simulate") == 0)
    //     {
    //         ntrials = 1;
    //     }
    //     // else "analyze"
    //     else if (strcmp(argv[4], "analyze") == 0)
    //     {
    //         ntrials = 1000;
    //     }
    //     else
    //     {
    //         printf("Invalid argument given");
    //         return -1;
    //     }
    // }
    // else
    // {
    //     ntrials = 100;
    // }

    // Use getopt to retrieve command line arguments (vprob, tprob, output file, simulate/analyze, ntrials)

    if (argc != 9)
    {
        printf("Invalid number of arguments\n");
        return -1;
    }

    int opt;

    while ((opt = getopt(argc, argv, "v:t:o:n:")) != -1)
    {
        switch (opt)
        {
        case 'v':
            vprob = atoi(optarg);
            break;
        case 't':
            tprob = atoi(optarg);
            break;
        case 'o':
            output = fopen(optarg, "w");
            break;
        case 'n':
            ntrials = atoi(optarg);
            if (ntrials <= 0)
            {
                printf("Invalid value for ntrials");
                return -1;
            }
            break;
        default:
            printf("Invalid argument given");
            return -1;
        }
    }

    // Calculate number of vaccinated people
    int nvaccinated = (int)(vprob * npeople);

    for (trial = 0; trial < ntrials; trial++)
    {
        int realTrialNumber = trial + 1;

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
            sumDead += ndead;
            sumDeadSquared += ndead * ndead;
            sumRecovered += nrecovered;

            fprintf(output, "%d %d %d %d %d %d %d\n", day, trial, nsusceptible, nrecovered, nvaccinated, ninfected, ndead);
        }
    }

    printf("Population: %d\n", npeople);
    printf("Vaccination Probability: %lf\n", vprob);
    printf("Transmission Probability: %lf\n", tprob);
    printf("Initial Infections: %d\n", initial_infections);
    printf("Simulation Period: %d days\n", ndays);

    printf("Number of trials: %d\n", ntrials);
    printf("Average number of deaths: %lf\n", sumDead / ntrials);
    printf("Standard deviation of deaths: %lf\n", sqrt((sumDeadSquared - sumDead * sumDead / ntrials) / (ntrials - 1)));

    printf("Average number of recoveries: %lf\n", sumRecovered/ntrials);
    printf("Average Case Fatality Rate: %lf\n", (double)sumDead / (sumRecovered + sumDead));

    return 0;
}
