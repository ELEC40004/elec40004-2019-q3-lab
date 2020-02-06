#ifndef sum_wave_hpp
#define sum_wave_hpp

#include "wave.hpp"

#include "factory_parameters.hpp"

#include "wave_factory.hpp"

#include <cmath>
#include <vector>
#include <string>

class SumWave
    : public Wave
{
private:
    const Wave *m_wave1;
    const Wave *m_wave2;
public:
    SumWave(const factory_parameters &params)
    {
        if(params.args.size()!=2){
            cerr<<"SumWave need two arguments"<<endl;
        }
        m_wave1=wave_factory(params.args[0]);
        m_wave2=wave_factory(params.args[1]);
    }

    ~SumWave()
    {
        delete m_wave1;
        delete m_wave2;
    }

    virtual float evaluate(float t) const override
    {
        return m_wave1->evaluate(t) + m_wave2->evaluate(t);
    }
};

#endif
