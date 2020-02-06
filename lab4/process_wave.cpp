#include "wave.hpp"

#include "wave_factory.hpp"
#include "sink_factory.hpp"

int main(int argc, const char **argv)
{
    string wave_spec_string = "square";
    string sink_spec_string = "csv";

    if(argc>1){
        wave_spec_string = argv[1];
    }
    if(argc>2){
        sink_spec_string = argv[2];
    }

    const Wave *wave = wave_factory( parse_factory_parameters( wave_spec_string ) );
    const Sink *sink = sink_factory( parse_factory_parameters( sink_spec_string ) );

    sink->output(wave);

    delete wave;
    delete sink;
}