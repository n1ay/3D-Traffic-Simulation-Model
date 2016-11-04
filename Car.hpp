#ifndef CAR_HPP_
#define CAR_HPP_

#include "Road.hpp"

class Car {
private:
	int velocity;
	int position;
	Road* road;

public:
	Car(Road* road);
	~Car();
	void update();
	bool checkFrontDistance();
};

#endif /* CAR_HPP_ */
