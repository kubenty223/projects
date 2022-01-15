#ifndef OBJECT_GENERATOR
#define OBJECT_GENERATOR

#include "..\obiekty\fruit.h"
#include "..\obiekty\bomb.h"
#include "..\obiekty\bowl.h"
#include <list>
#include <random>


class ObjectGenerator{
public:
	ObjectGenerator() {
		
	}
	static std::list<MapObject*> getobject();

	static int Random(int begin, int end);

	static bowl getbowl();
};

#endif