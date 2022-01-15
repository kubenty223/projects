#include "ObjectGenerator.h"

bowl ObjectGenerator::getbowl() {
	return bowl(90, 50, { 100,850 }, "miska.jpg");
}

//tworzymy listê wskaŸników na MapObject, nastêpnie wpsiujemy do niej po jednej losowo wygenerowanej bombie i owocu
 std::list<MapObject*>  ObjectGenerator::getobject() {
	std::list<MapObject*> generatedobject;
	static int dice_roll_bomb = Random(0, 1253);
	static int dice_roll_fruit = Random(0, 1253);
	sf::Vector2f rand_bomb(dice_roll_bomb, 0);
	sf::Vector2f rand_fruit(dice_roll_fruit, 0);
	generatedobject.push_back(new bomb(50, 55, rand_bomb, "bomba.jpg"));
	generatedobject.push_back(new fruit(55, 46, rand_fruit,"owoc.jpg"));
return generatedobject;
}

 //mersenne twister, funkcja zwraca losow¹ liczbê ca³kowit¹ w podanym przez u¿ytkownika zakresie
int ObjectGenerator::Random(int begin, int end) {
	std::random_device device;
	std::mt19937_64 generator(device());
	std::uniform_int_distribution<int> dist(begin, end);
	int rand_pos = dist(generator);

	return rand_pos;

}

