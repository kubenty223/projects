#ifndef CATCH_ENGINE
#define CATCH_ENGINE

#include "..\obiekty\fruit.h"
#include "..\obiekty\bomb.h"
#include "..\obiekty\bowl.h"
#include <iostream>

class CatchEngine {
	bowl& miska;

public:
	CatchEngine(bowl& miska) :
		miska(miska){

	}
	bool iscaught(MapObject* object);

	bool bordertouch(MapObject* object);
};

#endif
