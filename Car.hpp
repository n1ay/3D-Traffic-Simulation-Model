#ifndef CAR_HPP_
#define CAR_HPP_

#include <iostream>

//forward declaration of Lane
class Lane;

class Car {

private:
	Lane* lane;
	int position;
	int velocity;

public:
	Car();
	Car(Lane* road);
	~Car();
	friend std::ostream & operator<<(std::ostream & stream, const Car & car);
	void update();
	int checkFrontDistance();
	Car* copy(Lane* lane);
};

#endif /* CAR_HPP_ */
