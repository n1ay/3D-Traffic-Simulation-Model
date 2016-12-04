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

public:
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
};

#endif /* CAR_HPP_ */
