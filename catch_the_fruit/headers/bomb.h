#ifndef BOMB
#define BOMB

#include "MapObject.h"
#include "..\engine\Score.h"
class bomb : public MapObject {
public:
	

	bomb(int width, int height, sf::Vector2f startposition, std::string filename) : MapObject(width, height,startposition, filename){
	}

	void oncatch() override {
		Score* b = Score::GetInstance();
		b->loselife();
	}
};

#endif