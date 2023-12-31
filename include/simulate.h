#pragma once

#ifndef SIMULATE_H
#define SIMULATE_H

#include <stdlib.h>

int catch_or_not(double tprob, int npeople, int status[]);

int die_or_not(double dprob, int sick_days, int person, int npeople, int status[]);

#endif // SIMULATE_H
