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
	Lane* doChangeLane();
};

#endif /* CAR_HPP_ */
