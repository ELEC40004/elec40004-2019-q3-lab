#ifndef vector2d_hpp
#define vector2d_hpp

#include <iostream>
#include <iomanip>

using namespace std;

//////////////////////////////////////////////
// Public API

struct vector2d
{
    float x;
    float y;
};

// This are operators allowing us to do "normal" maths on points
vector2d operator+(const vector2d &a, const vector2d &b);
vector2d operator-(const vector2d &a, const vector2d &b);
vector2d operator*(const vector2d &a, float s);

// Read and write vectors using the syntax in definition
ostream &operator<<(ostream &dst, const vector2d &a);
istream &operator>>(istream &dst, vector2d &a);


#endif
