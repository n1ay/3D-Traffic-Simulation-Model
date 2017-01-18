#ifndef CAR_HPP_
#define CAR_HPP_

#include <iostream>

//forward declaration of Lane
class Lane;

class Car {

private:
	Lane* lane;
	int length;
	int position;
	int velocity;
	bool changedLane = false;
	Lane* destination = nullptr;
	bool doAccelerate = true;
	bool alreadyUpdated = false;

public:
	static int count;
	Car();
	Car(Lane* road, int length);
	~Car();
	friend std::ostream & operator<<(std::ostream & stream, const Car & car);
	void update();
	int checkFrontDistance();
	int getLength();
	Car* copy(Lane* lane);
	void changeLane(Lane * lane);
	void putInLane(Lane* lane);
	Lane* doChangeLane(bool next);
	void setDestination(Lane* destination);
	Lane* getDestination();
	int getFrontDistance();
	void setLane(Lane* lane);
	void setPosition(int position);
	int moveSmooth();
	void setUpdated(bool updated);
};

#endif /* CAR_HPP_ */
