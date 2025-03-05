#include "Display.h"

int main()
{
    Display display;
    display.setResolution(800, 600);
    display.setTitle("PGK2 projekt");
    display.activateWindow();
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    while (display.getWindow()->isOpen())
    {
        while (const std::optional event = display.getWindow()->pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                display.getWindow()->close();
        }
        display.getWindow()->clear();
        display.getWindow()->draw(shape);
        display.getWindow()->display();
    }
}