#include "engine/Catchengine.h"
#include "engine/ObjectGenerator.h"
#include "engine/Display.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 960), "Catch the fruit");
    window.setVerticalSyncEnabled(true);
    
    display punkty("arial.ttf", { 640,0 });
    display zycia("arial.ttf", { 640,25 });
    display splash_screen("arial.ttf", { 640,480 });

    bowl miska(ObjectGenerator::getbowl());
    std::list<MapObject*> obiekt(ObjectGenerator::getobject());

    CatchEngine engine(miska);

    Score* score = Score::GetInstance();

    bool is_playing = false;
    
    while (window.isOpen()) {
        
        sf::Event event;

        //sprawdzanie warunków zakoñczenia gry
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))) {
                window.close();
                break;
            }
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space)) {
                if(!is_playing){
                    is_playing = true; // rozpoczynamy grê po wczeœniejszym sprawdzeniu czy zosta³a wciœniêta spacja
                }
            }
        }
        if(is_playing){
        //losowanie pozycji i tworzenie nowych obiektów
            int r = ObjectGenerator::Random(0, 100);

            if (r == 3) {
                int rand = ObjectGenerator::Random(0, 1260);
                sf::Vector2f randpos(rand, 0);
                obiekt.emplace_front(new bomb(50, 55, randpos, "bomba.jpg"));

            }
            else if (r > 99) {
                int rand = ObjectGenerator::Random(0, 1260);
                sf::Vector2f randpos(rand, 0);
                obiekt.emplace_front(new fruit(55, 46, randpos, "owoc.jpg"));
            }
        
        
            window.clear(sf::Color::White);

            // wyœwietlanie tablicy wyników i ¿yæ
            punkty.set_text("Score: " + std::to_string(score->getScore()));
            zycia.set_text("Lives: " + std::to_string(score->getlives()));

            zycia.show(window);
            punkty.show(window);

            //umieszczenie miski na planszy oraz obs³uga poruszania ni¹
            miska.draw(window);
            miska.routine();

            //rysowanie obiektów i ich poruszanie
            for (auto obj : obiekt) {
                obj->draw(window);
                obj->fall_routine();
            }

            //sprawdzanie kolizji, usuwanie obiektów z planszy, naliczanie punktów i odejmowanie ¿yæ
            for (auto obj : obiekt) {   
                    if (obiekt.size() > 0) {
                        if (engine.bordertouch(obj)) {
                            obj->onfall();
                            obiekt.pop_back();
                            break;
                        }
                        if (engine.iscaught(obj)) {
                            obj->oncatch();
                            obiekt.pop_back();
                            break;
                        }                                                   
                    }
            }
            //zakonczenie gry, reset punktów i ¿yæ, czyszczenie tablicy obiektów
            if (score->getlives() == 0 || score->getScore() < 0) {
                obiekt.clear();
                score->setlife();
                score->addToScore(score->getScore()*-1);
                is_playing = false;
            }
        }
        else {
            window.clear(sf::Color::White);
            splash_screen.set_text("PRESS SPACE TO BEGIN");
            splash_screen.show(window);
        }
        window.display();
    }
    return 0;
}