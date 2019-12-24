#include "drawing.hpp"

#include <sstream>

string make_colour(float r, float g, float b)
{
    assert( 0<=r && r<=1.0);
    assert( 0<=g && g<=1.0);
    assert( 0<=b && b<=1.0);
    stringstream tmp;
    tmp<<"rgb("<<int(255*r)<<","<<int(255*g)<<","<<int(255*b)<<")";
    return tmp.str();
}

int main()
{
    Drawing d;
    
    // Note: this is very naughty, but if we only have structures we can't stop the user doing it.
    d.min_x=-1.0;
    d.min_y=-1.0;
    d.max_x=1.0;
    d.max_y=1.0;

    float PI2=6.2831853f;

    for(int i=0; i<1024; i++){
        double x=sin(i/128.0*PI2)*100*((1024-i)/1024.0);
        double y=cos(i/128.0*PI2)*100*((1024-i)/1024.0);
        float r=sin(i/64.0)*0.5+0.5;
        float g=sin(i/60.0)*0.5+0.5;
        float b=sin(i/50.0)*0.5+0.5;
        Drawing_add_circle(&d, make_colour(r,g,b), x, y, sin(i/50.0)*3+4);
    }

    Drawing_write_svg(&d);
}