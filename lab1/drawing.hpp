#ifndef drawing_hpp
#define drawing_hpp

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cfloat>
#include <cassert>

using namespace std;

struct Polygon
{
    string colour;
    vector<float> x;
    vector<float> y;
};

struct Drawing
{
    float min_x, max_x;
    float min_y, max_y;
    vector<Polygon> shapes;
};

/* Construct a new drawing. */
Drawing *Drawing_create()
{
    Drawing *res=new Drawing;
    // Bounds are initialised to maximum/minimum possible.
    res->min_x=FLT_MAX;
    res->max_x=-FLT_MAX;
    res->min_y=FLT_MAX;
    res->max_y=-FLT_MAX;
    return res;
}

void Drawing_destroy(Drawing *d)
{
    // Currently there is nothing interesting to do here apart from deallocate the object.
    delete d;
}

// Add a copy of the given polygon instance to the drawing.
void Drawing_add_polygon(Drawing *d, Polygon p)
{
    int len=p.x.size(); // Number of points in the polygon

    // min_element finds the smallest element in a range of pointers
    float *pMin=min_element( &p.x[0], &p.x[len] );
    d->min_x = min( d->min_x, *pMin);

    // Contracted version of the above
    d->max_x = max( d->max_x, *max_element( &p.x[0], &p.x[len] ) );
    d->min_y = min( d->min_y, *min_element( &p.y[0], &p.y[len] ) );
    d->max_y = max( d->max_y, *max_element( &p.y[0], &p.y[len] ) );
    
    d->shapes.push_back(p);
}

// Adds a square with corners at (x1,y1) to (x2,y2)
void Drawing_add_square(Drawing *d, string colour, float x1, float y1, float x2, float y2)
{
    Polygon square={colour,
        {x1,x2,x2,x1},
        {y1,y1,y2,y2}
        };
    Drawing_add_polygon(d, square);
}

// Adds a triangle with vertices at (x1,y1), (x2,y2), (x3,y3)
void Drawing_add_triangle(Drawing *d, string colour, float x1, float y1, float x2, float y2, float x3, float y3)
{
    Polygon square={colour,
        {x1,x2,x3},
        {y1,y2,y3}
        };
    Drawing_add_polygon(d, square);
}

// Adds a circle centered at (x,y) with radius r
void Drawing_add_circle(Drawing *d, string colour, float x, float y, float r)
{
    Polygon circle;
    circle.colour=colour;
    int n=16; // Currently we don't implement a true circle, it is actually a polygon
    float PI2=6.2831853f;
    for(int i=0; i<n; i++){
        float fraction=i/float(n);
        circle.x.push_back( x + sin(fraction*PI2) * r );
        circle.y.push_back( y + cos(fraction*PI2) * r );
    }
    Drawing_add_polygon(d, circle);
}

// This writes the current drawing out to cout in SVG format
void Drawing_write_svg(Drawing *d)
{
    assert(!d->shapes.empty());

    float off_x=d->min_x;
    float off_y=d->min_y;
    float width=d->max_x-d->min_x;
    float height=d->max_y-d->min_y;

    while(min(width,height) < 256){
        width=width*1.5;
        height=height*1.5;
    } 

    while(max(width,height) > 1024){
        width=width/1.5;
        height=height/1.5;
    } 

    cout<<"<?xml version='1.0' encoding='UTF-8'?>"<<endl;
    cout<<"<svg xmlns='http://www.w3.org/2000/svg' height='"<<height<<"' width='"<<width<<"'"<<endl;
    cout<<"  viewBox='"<<d->min_x<<" "<<d->min_y<<" "<<d->max_x-d->min_x<<" "<<d->max_y-d->min_y<<"' >" << endl;
    for(unsigned i=0; i<d->shapes.size(); i++){
        cout<<"  <polygon style='fill:"<<d->shapes[i].colour<<"' points='";
        for(unsigned j=0; j<d->shapes[i].x.size(); j++){
            cout<<" "<<d->shapes[i].x[j]<<","<<d->shapes[i].y[j];
        }
        cout<<"' />"<<endl;
    }
    cout<<"</svg>"<<endl;
}

#endif
