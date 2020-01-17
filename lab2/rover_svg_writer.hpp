#ifndef rover_svg_hpp
#define rover_svg_hpp

#include "rover.hpp"

#include <cassert>
#include <cmath>
#include <algorithm>

Rover::Rover()
{
    cout<<"<?xml version='1.0' encoding='UTF-8'?>"<<endl;
    cout<<"<svg xmlns='http://www.w3.org/2000/svg' "; // height='256' width='256'"<<endl;
    cout<<"  viewBox='-1.1 -1.1 2.2 2.2' >" << endl;

    m_time=0;
    m_angle=0;
    m_position={0,0};
    m_speed=0;
    m_pen_down=false;
}

Rover::~Rover()
{
    cout<<"</svg>"<<endl;
}

float Rover::get_time() const
{
    return m_time;
}

vector2d Rover::get_position() const
{
    return m_position;
}

float Rover::get_speed() const
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

    if(m_pen_down){
        float width = max(0.001, min(0.01, 1.0/m_speed));

        cout << "  <line x1 = '"<<p.x<<"' y1 = '"<<p.y<<"' x2 = '"<<pn.x<<"' y2 = '"<<pn.y<<"' stroke = 'black' stroke-width = '"<<width<<"'/>" << endl;
    }

    m_time += dt;
    m_position=pn;
}

#endif
