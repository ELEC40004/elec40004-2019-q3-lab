#include "rover.hpp"

#include <cmath>

int main(int argc, const char **argv)
{
    float PI=3.14159265;

    Rover r;
    r.set_angle(PI/4);
    r.set_speed(1);
    r.advance_time(sqrt(2));

    r.set_pen_down(true);
    float angle=PI;
    float time_step=2;
    while(time_step > 1e-3){
        r.set_angle(angle);
        r.advance_time( time_step );

        angle = angle + PI/2 + 0.05;
        time_step=time_step*0.95;
    }
}