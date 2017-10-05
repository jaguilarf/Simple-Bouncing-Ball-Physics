#ifndef _BALL_HPP
#define _BALL_HPP

#include <SFML/Graphics/CircleShape.hpp>

class BALL
{
private:
    float velocity = 0.04;
    float wind_strength = 0.02;
    const float decrease_velocity = velocity * 250;

    int x;
    int y;
    int max_height = y;
    const int ballRadius = 21;
    const int yDevider = 10;
    const int decrease_height = decrease_velocity * 2;
    
    bool touching_ground;
    bool wind_right = true;
    bool stopped_bouncing = false;

private: 
    void on_ground()
    {
        if(ball.getPosition().y >= y  - (ballRadius * 2))
            touching_ground = true;
        else
            touching_ground = false;
    }

public:
    sf::CircleShape ball;
    bool dont_draw = false;

    void setup_appearance(int r, int g, int b, int winXPos, int winY, int winX)
    {
        ball.setRadius(ballRadius);
        ball.setFillColor(sf::Color(r, g, b));
        ball.setPosition(winXPos - 30, winY / yDevider);

        x = winX;
        y = winY;
    };

    void setup_physics(float vel, bool wind_to_right, float wind_str)
    {
        velocity = vel;
        wind_right = wind_to_right;
        wind_strength = wind_str;
    }

    void physics()
    {
        // Touching Ground?
        static bool once= true;
        if(once)
        {
            on_ground();
            once = false;
        }

        if(!stopped_bouncing)
        {
            //Move Down
            if(!touching_ground)
            {
                ball.move(0, velocity);

                if(ball.getPosition().y >= y  - (ballRadius * 2))
                {
                    touching_ground = true;
                    //Decrease Velocity
                    velocity -= velocity / decrease_velocity;
                }
            }
            // Go Up
            else
            {
                ball.move(0, -velocity);

                if(ball.getPosition().y <= max_height)
                {
                    touching_ground = false;
                    //Decrease Height
                    max_height = max_height + decrease_height;
                }
            }

            // Move Ball
            if(wind_right)
                ball.move(wind_strength, 0);
            else
                ball.move(-wind_strength, 0);

            // Touching left wall
            if(ball.getPosition().x >= x - (ballRadius * 2)) 
                wind_right = false;
            
            // Touching Right wall
            else if(ball.getPosition().x <= 0) 
                wind_right = true; 

            if(max_height / 100 >= y)
            {
                dont_draw = true;
                stopped_bouncing = true;
            }
        }
    }
};
#endif
