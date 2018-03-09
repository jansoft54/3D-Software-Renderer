#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "Engine.h"


using namespace sf;

RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
int main()
{

    Clock clock;

    float fps = 0;


    Engine engine(window);
    window.setFramerateLimit(60);
    while (window.isOpen())
    {
      if(clock.getElapsedTime().asSeconds() > 1)
      {
          clock.restart();

          std::cout << fps<< '\n';
          fps = 0;
      }
        engine.Update(1/60.0);
        window.display();
        window.clear();
        fps++;
    }



         return 0;
        }







