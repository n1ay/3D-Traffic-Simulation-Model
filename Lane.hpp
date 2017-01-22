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
class Model;

class Lane {

	friend class Car;
	friend std::ostream & operator<<(std::ostream &, const Lane &);

private:
	friend class FrameParser;
	Road* road;
	int direction;
	int length;
	bool toCrossroad = false;
	float spawnProbability = 0.0f;
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
	void allowUpdate();

	int getLength();
	Lane* seekLane(bool next);
	void updateCarChangeLane(bool next);
	void putCar(Car* car, int position);
	bool isUsed(int position, int length);
	bool getCrossInfo();
	void setCrossInfo(bool set);
	void changeLight();
	void setTrafficLight(TrafficLight* trafficLight);
	TrafficLight* getTrafficLight();
	void setSpawnProbability(float probability);
	void trySpawn();
	int getVehicleLength();
};

#endif /* LANE_HPP_ */
