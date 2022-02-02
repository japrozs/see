#ifndef PPMODEL_H
#define PPMODEL_H

#include <mobility_model.h>

class Location;

#define NUM_POPULAR_PLACES 15
#define DISTANCING_PROBABILITY 0.8
#define DISTANCING_HOME_PROABILITY 0.997
#define NOT_DISTANCING_HOME_PROABILITY 0.2

#define PP_TOP_SPEED 20
#define MAX_STAY 4

class PopularPlacesModel : MobilityModel{
	private:
		Location *waypoint;
		Location *home;
		int speed, stay;
		double home_probability;

	public:
		PopularPlacesModel();
		void pick_new_waypoint();
		void move();
};

#endif // PPMODEL_H