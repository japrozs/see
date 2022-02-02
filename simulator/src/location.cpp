#include <location.h>
#include <simulator.h>

#include <math.h>
#include <stdlib.h>

#define CLOSE_ENOUGH 0.05

Location::Location(){
	x = arc4random_uniform(X_LIMIT);
	y = arc4random_uniform(X_LIMIT);
}

Location::Location(double nx, double ny){
	x = nx;
	x = ny;
}

bool Location::move_toward(Location destination, double howfar){
	double dx = destination.x;
	double dy = destination.y;
	double theta = atan2(dy, dx);

	double distance = sqrt((dx * dx) + (dy * dy));

	if(distance < howfar){
		x = destination.x;
		y = destination.y;

		return true;
	} else {
		x = x + (howfar * cos(theta));
		y = y + (howfar * sin(theta));

		return false;
	}
}

double Location::get_distance(Location other_location){
	double dx = other_location.x;
	double dy = other_location.y;

	return sqrt((dx * dx) + (dy * dy));
}

bool Location::at_location(Location destination){
	return (get_distance(destination) < CLOSE_ENOUGH);
}

double Location::getX(){ return x; }
double Location::getY(){ return y; }
void Location::setX(double nx){ x = nx; }
void Location::setY(double ny){ y = ny; }