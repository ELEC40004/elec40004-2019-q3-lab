#ifndef rover_action_hpp
#define rover_action_hpp

#include <iostream>
#include <cassert>

using namespace std;

struct RoverAction
{
    float dt;
    float angle;
    float speed;
    bool pen_down;
};

ostream &operator<<(ostream &dst, const RoverAction &a)
{
    ios::fmtflags flags = dst.flags();
    int prec = dst.precision(6);
    dst << fixed;

    dst << "Action ";
    dst << a.dt << " " << a.angle << " " << a.speed <<  " " << a.pen_down;

    dst.flags(flags);
    dst.precision(prec);
    
    return dst;
}

istream &operator>>(istream &src, RoverAction &a)
{
    string header;
    src >> header;
    assert(header=="Action");
    src >> a.dt >> a.angle >> a.speed >> a.pen_down;
    assert(!src.fail());
    return src;
}

#endif
