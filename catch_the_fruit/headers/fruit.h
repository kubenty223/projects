#ifndef FRUIT
#define FRUIT

#include "MapObject.h"
#include "../engine/Score.h"

class fruit : public MapObject {

public:
	

	fruit(int width, int height, sf::Vector2f startposition, std::string filename) : MapObject(width, height,startposition, filename){
	}

	void oncatch() override {
		Score* f = Score::GetInstance();
		f->addToScore(10);
	}

	void onfall() override {
		Score* f = Score::GetInstance();
		f->losescore(10);
	}
};

#endif
