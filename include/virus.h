#pragma once

#ifndef VIRUS_H
#define VIRUS_H

// Global variables:

// Counters:
extern int nsusceptible, ninfected, nrecovered, nvaccinated, ndead;

// Status indicators:
// Any positive value indicates user has been infected for n days.
extern const int is_infected;

// Negative values indicate:
extern const int is_susceptible;
extern const int is_recovered;
extern const int is_vaccinated;
extern const int is_dead;

// Function that updates status of each person and counts them
void update_status(int npeople, int status[], int newstatus[]);

/* Function that sets up the initial health status of all 10,000 people.
    Person will either be set to infected, vaccinated, or susceptible state.*/
void initialize_status (int npeople,int initial_infections, int nvaccinated, int status[]);

#endif // VIRUS_H
