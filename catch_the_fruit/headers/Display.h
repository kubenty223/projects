#ifndef DISPLAY
#define DISPLAY 
#include <SFML/Graphics.hpp>
class display {
	sf::Text tekst;
	sf::Font font;
public:
	display(std::string font_filename, sf::Vector2f position){
		font.loadFromFile(font_filename);
		tekst.setCharacterSize(24);
		tekst.setFillColor(sf::Color::Black);
		tekst.setFont(font);
		tekst.setPosition(position);
	}
	
	void set_text(std::string text) {
		tekst.setString(text);
	}

	void show(sf::RenderWindow& window) {
		window.draw(tekst);
	}


};

#endif
