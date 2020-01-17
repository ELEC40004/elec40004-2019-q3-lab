#ifndef rover_anim_hpp
#define rover_anim_hpp

#include "rover.hpp"

#include "rover_action.hpp"

#include <cassert>
#include <cmath>
#include <algorithm>

Rover::Rover()
{
    m_time=0;
    m_angle=0;
    m_position={0,0};
    m_speed=0;
    m_pen_down=false;
}

Rover::~Rover()
{
}

float Rover::get_time() const
{
    return m_time;
}

vector2d Rover::get_position()  const
{
    return m_position;
}

float Rover::get_speed()  const
{
    return m_speed;
}

float Rover::get_angle() const
{
    return m_angle;
}

bool Rover::get_pen_down() const
{
    return m_pen_down;
}

void Rover::set_speed(float speed)
{
    assert(speed >= 0);
    m_speed=speed;
}

void Rover::set_angle(float angle)
{
    m_angle=angle;
}

void Rover::set_pen_down(bool pen_down)
{
    m_pen_down=pen_down;
}

void Rover::advance_time(float dt)
{
    vector2d p = m_position;
    vector2d direction = vector2d{ cos(m_angle) , sin(m_angle) } ;
    vector2d pn = m_position + direction * dt * m_speed;

    cout << RoverAction{dt, m_angle, m_speed, m_pen_down} << endl;

    m_time += dt;
    m_position=pn;

    // Diagnostic information being printed out. This goes to a 
    // different place than cout, and is not part of the program output.
    cerr << "New position at " << m_time << " is " << m_position << endl;
}

#endif
