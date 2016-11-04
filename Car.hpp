#ifndef CAR_HPP_
#define CAR_HPP_

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
	void update();
	bool checkFrontDistance();
};

#endif /* CAR_HPP_ */
