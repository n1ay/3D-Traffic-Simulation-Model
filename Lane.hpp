#ifndef LANE_HPP_
#define LANE_HPP_

#include <iostream>
#include <vector>
#include "TrafficLight.hpp"

enum Direction {
	LEFT = 0,
	RIGHT = 1
};

//forward declaration of Car
class TrafficLight;
class Car;
class Road;

class Lane {

	friend class Car;
	friend std::ostream & operator<<(std::ostream &, const Lane &);

private:
	Road* road;
	int direction;
	int length;
	bool toCrossroad = true;
	std::vector<Car*> lanes[2];
	TrafficLight* trafficLight;


public:

	Lane(Road* road, int direction, int length);
	~Lane();

	void spawnCar(int length);
	void moveCar(int from, int to);
	Car* getCar(int from);
	void removeCar(int position);

	void update();
	void cleanUpdate();
	void lockUpdate();

	int getLength();
	void log();
	Lane* seekLane(bool next);
	void updateCarChangeLane(bool next);
	void putCar(Car* car, int position);
	bool isUsed(int position, int length);
	bool getCrossInfo();
	void setCrossInfo(bool set);
	void changeLight();
	void setTrafficLight(TrafficLight* trafficLight);
	TrafficLight* getTrafficLight();
};

#endif /* LANE_HPP_ */
