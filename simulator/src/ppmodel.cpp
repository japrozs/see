#include <ppmodel.h>
#include <location.h>
#include <simulator.h>
#include <person.h>
#include <stdlib.h>

static Location popularPlaces[NUM_POPULAR_PLACES];

PopularPlacesModel::PopularPlacesModel() : MobilityModel(){
	speed  = -1;
	home = new Location();
	if(try_event(DISTANCING_PROBABILITY)){
		home_probability = DISTANCING_HOME_PROABILITY;
	}else{
		home_probability = NOT_DISTANCING_HOME_PROABILITY;
	}

}

void PopularPlacesModel::move(){
	if(speed < 0){
		person->location.setX(home->getX());
		person->location.setY(home->getY());
		pick_new_waypoint();
	}else if(person->location.at_location(*waypoint)){
		stay--;
		if(stay <= 0){
			pick_new_waypoint();
		}
	} else{
		person->location.move_toward(*waypoint, speed);
	}
}

void PopularPlacesModel::pick_new_waypoint(){
	speed = arc4random_uniform(PP_TOP_SPEED) + 1;
	stay = arc4random_uniform(MAX_STAY);

	if(try_event(home_probability)){
		waypoint = home;
	}else{
		int place = arc4random_uniform(NUM_POPULAR_PLACES);
		waypoint = &(popularPlaces[place]);
	}
}