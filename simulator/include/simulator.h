#ifndef SIMULATOR_H
#define SIMULATOR_H

#define X_LIMIT 5000
#define Y_LIMIT 5000

#define SIM_HOURS 5000
#define NUM_PEOPLE 1000

enum disease_status {VULNERABLE, INFECTED, IMMUNE, DEAD};

#define INFECTION_TIME (24 * 20)

#define INFECTION_PROBABILITY 0.5

#define NORMAL_FATALITY_RATE 0.01
#define SATURATED_FATALITY_RATE 0.06
#define INFECTION_PROXIMITY 5.0
#define INITIAL_INFECTIONS 5

#define SATURATED_THRESHOLD (NUM_PEOPLE / 5)

extern bool saturated;

bool try_event(double probability);

#endif // SIMULATOR_H