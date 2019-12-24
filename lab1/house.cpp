#include "drawing.hpp"

int main()
{
    Drawing *d=Drawing_create();

    Drawing_add_square(d, "green", 0.0,6.0, 10.0,10.0);
    Drawing_add_square(d, "blue", 0.0,0.0, 10.0,6.0);

    Drawing_add_square(d, "orange", 1.0,9.0, 9.0,4.0);
    Drawing_add_triangle(d, "darkred", 1.0,4.0, 5.0,1.0, 9.0,4.0);

    Drawing_add_square(d, "white", 2,5, 3.5,6.5);
    Drawing_add_square(d, "white", 8,5, 6.5,6.5);
    Drawing_add_square(d, "grey", 4,9, 6,5);
    Drawing_add_square(d, "darkred", 2,4, 3,2);

    Drawing_write_svg(d);

    Drawing_destroy(d);
}