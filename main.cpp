#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <ctime>

#include "ball.hpp"

#define windowX 500
#define windowY 800

#define maxBalls 30

float random_float(float a, float b)
{
    return ((b - a) * ((float)rand() / RAND_MAX)) + a;
}

int main()
{
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(windowX, windowY), "Ball Simulations");

    BALL balls[maxBalls];
    for(int i = 0; i < maxBalls; i++)
    {
        balls[i].setup_appearance(static_cast<int>(random_float(0, 255)), 
            static_cast<int>(random_float(0, 255)), static_cast<int>(random_float(0, 255)), 
            random_float(0, windowX), windowY, windowX);
        balls[i].setup_physics(random_float(0.04, 0.3), true, 0.008);
    }

    while(window.isOpen())
    {
        sf::Event event;

        while(window.pollEvent(event))
            if(event.type == sf::Event::Closed)
                window.close();

        for(int i = 0; i < maxBalls; i++)
            balls[i].physics();

        window.clear(sf::Color::White);

        for(int i = 0; i < maxBalls; i++)
            if(!balls[i].dont_draw)
                window.draw(balls[i].ball);
        
        window.display();
    }
}