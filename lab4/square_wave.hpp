#ifndef square_wave_hpp
#define square_wave_hpp

#include "wave.hpp"

#include "factory_parameters.hpp"

#include <cmath>
#include <vector>
#include <string>

class SquareWave
    : public Wave
{
private:
    float m_frequency;
    float m_amplitude;
    float m_phase;
public:
    SquareWave(const factory_parameters &params)
    {
        m_frequency=params.get_float_arg(0, 1.0);
        m_amplitude=params.get_float_arg(1, 1.0);
        m_phase=params.get_float_arg(1, 0.0);
    }

    virtual float evaluate(float t) const override
    {
        float wavelength=1/m_frequency;

        if(t < 0){
            return evaluate(-t+wavelength/2);
        }
        if( fmod(t+m_phase, wavelength) < wavelength/2){
            return -m_amplitude;
        }else{
            return +m_amplitude;
        }
    }
};

#endif
