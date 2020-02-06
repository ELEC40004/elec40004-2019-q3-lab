#ifndef wave_hpp
#define wave_hpp

#include <vector>
#include <string>

using namespace std;

class Wave
{
private:
    // Stop other people constructing or assigning it
    Wave &operator=(const Wave &);
    Wave(const Wave &);
protected:
    // Only derived classes can construct
    Wave()
    {}
public:
    virtual ~Wave()
    {}
    
    // Return the value of wave at time t
    virtual float evaluate(float t) const =0;
};

#endif
