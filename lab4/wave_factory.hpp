#ifndef wave_factory_hpp
#define wave_factory_hpp

#include <string>
#include <vector>

#include "wave.hpp"

#include "factory_parameters.hpp"

using namespace std;

const Wave *wave_factory(const factory_parameters &spec);

#endif