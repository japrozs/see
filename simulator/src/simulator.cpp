#include <iostream>
#include <math.h>
#include <assert.h>

#include <simulator.h>
#include <person.h>
#include <location.h>
#include <stdlib.h>
#include <ui.h>

using namespace std;

bool saturated = true;

bool try_event(double probability){
	assert (probability >= 0.0 && probability <= 1.0);
	const int resolution = 100000;

	double rnum = arc4random_uniform(resolution);
	rnum = rnum / (double) resolution;
	return rnum <= probability;
}

int sim_main(){
	// setup
	Person people[NUM_PEOPLE];
	int infection_history[SIM_HOURS];

	memset(infection_history, 0, sizeof(infection_history));

	for(int i = 0;i < INITIAL_INFECTIONS;i++){
		people[i].status = INFECTED;
	}

	int max_infected_at_once = 0;

	for(int i =0;i < SIM_HOURS;i++){
		if((i % 2) == 0){
			ui_redraw(people, NUM_PEOPLE, infection_history, SIM_HOURS);
		}

		for(int p = 0;p < NUM_PEOPLE;p++){
			if(people[p].is_alive()){
				people[p].mobility_model->move();
				people[p].progress_disease();
			}
		}

		// try to infect
		for(int p =0;p < NUM_PEOPLE;p++){
			if(people[p].is_alive()){
				for(int p2 =0;p2 < NUM_PEOPLE;p2++){
					if(p != p2 && people[p2].is_alive()){
						people[p].try_infect(people[p2]);
					}
				}
			}
		}

		// report status
		int num_infected = 0;
		int num_immune = 0;
		int num_dead = 0;
		int num_vulnerable = 0;

		for(int p = 0;p < NUM_PEOPLE;p++){
			if(!people[p].is_alive()){
				num_dead++;
			}
			if(people[p].status == INFECTED){
				num_infected++;
			}
			if (people[p].status == IMMUNE){
				num_immune++;
			}
			if(people[p].status == VULNERABLE){
				num_vulnerable++;
			}
		}

		if(num_infected > max_infected_at_once){
			max_infected_at_once = num_infected;
		}

		saturated = (num_infected > SATURATED_THRESHOLD);
		if((i % 10) == 0 || num_infected == 0){
			printf("%i\t%i\t%i\t%i(%lf%%)\n", num_vulnerable, num_infected, num_immune, num_dead, (num_dead * 100.0/NUM_PEOPLE));
		}

		infection_history[i] = num_infected;
		if(num_infected == 0) break;
	}
	printf("Peak infections :: %i\n", max_infected_at_once);
	return 0;
}

int main(){
	return start_ui(sim_main);
}