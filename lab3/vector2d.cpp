#include "vector2d.hpp"

#include <cassert>

vector2d operator+(const vector2d &a, const vector2d &b)
{
    return vector2d{a.x+b.x,a.y+b.y};
}

vector2d operator-(const vector2d &a, const vector2d &b)
{
    return vector2d{a.x-b.x,a.y-b.y};
}

vector2d operator*(const vector2d &a, float s)
{
    return vector2d{a.x*s, a.y*s};
}

// in the form `(x,y)`, where x and y are the numeric values.
// Numeric values should be printed with exactly three decimal digits
// of accuracy, in non-scientific format (i.e. no exponent). Whitespace
// should not be inserted anywhere.
ostream &operator<<(ostream &dst, const vector2d &a)
{
    int p=dst.precision(3);
    auto f=dst.flags();

    dst << fixed << '(' << a.x << "," << a.y << ")";

    dst.precision(p);
    dst.flags(f);

    return dst;
}

// This should match the format using when printing, and you can assume that
// it is in the correct format. Note that whitespace _may_ appear before the
// the opening '(' character, but not whitespace will appear between the
// '(' and ')'
istream &operator>>(istream &src, vector2d &a)
{
    char lb, comma, rb;
    src >> lb >> a.x >> comma >> a.y >> rb;
    assert(lb=='(' && comma==',' && rb==')');
    return src;
}
