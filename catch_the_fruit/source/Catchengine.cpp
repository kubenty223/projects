#include "Catchengine.h"
#include<iostream>

bool CatchEngine::iscaught(MapObject* object) {
	sf::Vector2f center_object = object->get_center();
	sf::Vector2f center_bowl = miska.get_center();

	//sprawdzamy, czy odleg�o�ci �rodk�w miski i obiektu s� mniejsze ni� szeroko�� i wysoko�� miski
	if ((abs(center_object.x - center_bowl.x) <= miska.width) && (center_bowl.y - center_object.y <= miska.height)) {

		return true;
	}
	else {
		return false;
	}
}

bool CatchEngine::bordertouch(MapObject* object) {
	sf::Vector2f center_object = object->get_center();

	//sprawdzamy, czy obiekt przekroczy� doln� granic� okna
	if ((960 - center_object.y < object->height)) {
		return true;
	}
	else {
		return false;
	}
}
