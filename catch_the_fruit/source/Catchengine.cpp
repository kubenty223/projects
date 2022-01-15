#include "Catchengine.h"
#include<iostream>

bool CatchEngine::iscaught(MapObject* object) {
	sf::Vector2f center_object = object->get_center();
	sf::Vector2f center_bowl = miska.get_center();

	//sprawdzamy, czy odleg³oœci œrodków miski i obiektu s¹ mniejsze ni¿ szerokoœæ i wysokoœæ miski
	if ((abs(center_object.x - center_bowl.x) <= miska.width) && (center_bowl.y - center_object.y <= miska.height)) {

		return true;
	}
	else {
		return false;
	}
}

bool CatchEngine::bordertouch(MapObject* object) {
	sf::Vector2f center_object = object->get_center();

	//sprawdzamy, czy obiekt przekroczy³ doln¹ granicê okna
	if ((960 - center_object.y < object->height)) {
		return true;
	}
	else {
		return false;
	}
}
