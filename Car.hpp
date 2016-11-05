#ifndef CAR_HPP_
#define CAR_HPP_

#include <iostream>

//forward declaration of Road
class Road;

class Car {

private:
	Road* road;
	int position;
	int velocity;

public:
	Car();
	Car(Road* road);
	~Car();
	friend std::ostream & operator<<(std::ostream &, const Car &);
	void update();
	int checkFrontDistance();
};

#endif /* CAR_HPP_ */
