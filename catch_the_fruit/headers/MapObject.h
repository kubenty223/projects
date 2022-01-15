#pragma once

#ifndef MAP_OBJECT
#define MAP_OBJECT

#include<SFML/Graphics.hpp>
#include <iostream>

class MapObject {
	sf::Sprite sprite;
	sf::Texture texture;
public:
	sf::Vector2f moveVector;
	sf::Vector2f position;
	int width{};
	int height{};

	MapObject(int width, int height,sf::Vector2f startposition, std::string filename) : width(width), height(height), sprite(), texture(), position(0,0),moveVector(0,0) {
		texture.loadFromFile(filename);
		sprite.setTexture(texture);
		spawn(startposition);
	}
	void draw(sf::RenderWindow& window) {
		window.draw(sprite);
	}

	void fall_routine() {
		fall(moveVector);
	}

	void fall(sf::Vector2f moveVector) {
		moveVector = { 0,5 };
		position += moveVector;
		update_position(moveVector);
	}
	void spawn(sf::Vector2f spawnpoint) {
		position += spawnpoint;
		update_position(spawnpoint);
	}

	void update_position(sf::Vector2f newposition) {
		sprite.move(newposition);
	}
	virtual void oncatch() {
	}

	virtual void onfall() {
	}
	sf::Vector2f get_position() {
		return position;
	}

	sf::Vector2f get_center() {
		return sf::Vector2f(position.x + width / 2, position.y + height / 2);
	}
};

#endif




