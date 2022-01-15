#include <C:\Users\Kuba\Desktop\projekty\SFML\projekt\projekt\obiekty\bowl.h>

void bowl::check_key() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && (get_center().x + width < 1280)) {
		moveVector = sf::Vector2f{ 10,0 };
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && (get_center().x - width/2 > 0)) {
		moveVector = sf::Vector2f{ -10,0 };
	}
	else {
		moveVector = sf::Vector2f{ 0,0 };
	}
}

void bowl::move(sf::Vector2f moveVector) {
	position += moveVector;
	update_position(moveVector);
}