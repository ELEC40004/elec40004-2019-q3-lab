#include "factory_parameters.hpp"

void test_string(const std::string &input)
{
    cout<<"input  = "<<input<<endl;
    cout<<"parsed = " << parse_factory_parameters(input) <<endl;
    cout<<endl;
}

int main()
{
    test_string("square");
    test_string("[ square )");
    test_string("[ square 0.1 4.5 )");
    test_string("[ add 5 [ square 3.2 0.1 ] [ circle 4 ] ]");

    // Should fail
    test_string("[add 5[ square 3.2 0.1 ] [ circle 4 ] ]");
}