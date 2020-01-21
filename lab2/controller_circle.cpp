#include "rover.hpp"

#include <cmath>

#include "rover_svg_writer.hpp"

int main(int argc, const char **argv)
{
    Rover r;

    r.set_angle(0);
    r.set_speed(1);
    r.advance_time(1);

    // We are one the edge of the unit circle, and need to move
    // around it in n discrete steps. So we have n isoceles
    // triangles making up the circle, each with two sides of
    // length 1, and an angle of 2*pi/n.
    // Each triangle has base 2*r*sin(0.5*2*pi/n)
    //   step = 2*sin(pi/n)
    // The angle change at each step is 2*pi/n
    //   rotate = 2*pi/n

    float PI=3.141592653;

    int n=16;
    if(argc>1){
        n=atoi(argv[1]);
    }

    float step = 2*sin(PI/n);
    r.set_speed(1.0);

    r.set_pen_down(true);
    float angle = PI/2 + PI/(n);
    for(int i=0; i<n; i++){
        r.set_angle(angle);
        r.advance_time( step );

        angle += 2*PI/n;
    }


    r.set_pen_down(false);
    r.advance_time(1);
}