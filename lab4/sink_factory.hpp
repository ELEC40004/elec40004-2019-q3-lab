#ifndef sink_factory_hpp
#define sink_factory_hpp

#include <string>
#include <vector>

#include "sink.hpp"

#include "factory_parameters.hpp"

using namespace std;

const Sink *sink_factory(const factory_parameters &p);

#endif