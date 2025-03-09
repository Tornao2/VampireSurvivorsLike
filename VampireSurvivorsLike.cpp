#include "Display.h"

int main()
{
    Display display;
    display.setResolution(800, 600);
    display.setTitle("PGK2 projekt");
    display.turnOffCursor();
    display.setFramerate(60);
    display.setFullscreen(true);
    sf::CircleShape shape(100.0f);
    while (display.getWindow()->isOpen())
    {
        while (std::optional event = display.getWindow()->pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                display.getWindow()->close();
        }
        display.getWindow()->clear();
        display.getWindow()->draw(shape);
        display.getWindow()->display();
    }
}