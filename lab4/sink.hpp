#ifndef sink_hpp
#define sink_hpp

#include "wave.hpp"

/* Represents something that consumes or outputs a wave
*/
class Sink
{
public:
    virtual ~Sink()
    {}

    virtual void output(const Wave *wave) const =0;
};

#endif
