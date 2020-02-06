#include "wave_factory.hpp"

#include "square_wave.hpp"
#include "sum_wave.hpp"

using namespace std;

const Wave *wave_factory(const factory_parameters &spec)
{
    if(spec.verb=="square"){
        return new SquareWave(spec);
    }else if(spec.verb=="sum"){
        return new SumWave(spec);
    }else{
        cerr<<"Didn't understand wave spec verb '"<<spec.verb<<endl;
        exit(1);
    }
}
