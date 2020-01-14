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

int main(int argc, char **argv)
{
    Drawing d;

    float s1=128;
    if(argc>1){
        s1=strtof(argv[1], nullptr);
    }
    float s2=64;
    if(argc>2){
        s2=strtof(argv[2], nullptr);
    }
    float s3=60;
    if(argc>3){
        s3=strtof(argv[3], nullptr);
    }
    float s4=50;
    if(argc>3){
        s4=strtof(argv[4], nullptr);
    }
    float s5=50;
    if(argc>5){
        s5=strtof(argv[5], nullptr);
    }
    
    // Note: this is very naughty, but if we only have structures we can't stop the user doing it.
    d.min_x=-1.0;
    d.min_y=-1.0;
    d.max_x=1.0;
    d.max_y=1.0;

    float PI2=6.2831853f;

    Drawing_add_square(&d, "powderblue", -110,-110, 110,110);

    for(int i=0; i<1024; i++){
        double x=sin(i/s1*PI2)*100*((1024-i)/1024.0);
        double y=cos(i/s1*PI2)*100*((1024-i)/1024.0);
        float r=sin(i/s2)*0.5+0.5;
        float g=sin(i/s3)*0.5+0.5;
        float b=sin(i/s4)*0.5+0.5;
        Drawing_add_circle(&d, make_colour(r,g,b), x, y, sin(i/s5)*3+4);
    }

    Drawing_write_svg(&d);
}