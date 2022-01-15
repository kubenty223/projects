#ifndef BOWL
#define BOWL

#include "MapObject.h"

class bowl : public MapObject {
	sf::Vector2f position;
	sf::Vector2f moveVector;

public:
	bowl(int width, int height,sf::Vector2f startposition, std::string filename) :MapObject(width, height,startposition, filename), position(startposition), moveVector(0, 0) {
	}

	void routine() {
		check_key();
		move(moveVector);
	}

	void check_key();
	void move(sf::Vector2f moveVector);


	sf::Vector2f get_position() {
		return position;
	}

	sf::Vector2f get_center() {
		return sf::Vector2f(position.x + width / 2, position.y + height / 2);
	}
	
};

#endif