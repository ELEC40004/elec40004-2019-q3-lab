#ifndef rover_hpp
#define rover_hpp

#include "vector2d.hpp"

class Rover
{
private:
    float m_time;
    vector2d m_position;
    float m_angle;
    float m_speed;
    bool m_pen_down;
public:
    Rover();
    ~Rover();

    ////////////////////////////////////////
    // Find out the state of the rover.

    // Gets the state of the rover at the current point in time
    float get_time() const;
    vector2d get_position() const;
    
    float get_speed() const;
    float get_angle() const;
    bool get_pen_down() const;

    ////////////////////////////////////////
    // Modify the rover at the current time point
    
    // Set the speed, measured in unit distance per second
    void set_speed(float speed);

    // An angle in radians (will be reduced modulo 2pi)
    void set_angle(float angle);

    // Set to true to leave a trail behind, or false to move without drawing
    void set_pen_down(bool pen_down);

    ///////////////////////////////////////////
    // Manage state and time

    // Advance the rover forwards in time by `dt`, i.e. move to `get_time()+dt`
    // The rover will move at the current speed and angle for that time period.
    void advance_time(float dt);
};

#endif