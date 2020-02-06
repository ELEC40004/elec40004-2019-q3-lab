#ifndef csv_sink_hpp
#define csv_sink_hpp

#include "sink.hpp"

#include "factory_parameters.hpp"

/* Represents something that consumes or outputs a wave
*/
class CSVSink
    : public Sink
{
public:
    float m_t0;
    float m_t1;
    float m_dt;

public:
    CSVSink(const factory_parameters &p)
    {
        m_t0=p.get_float_arg(0, -10.0);
        m_t1=p.get_float_arg(1, 10.0);
        m_dt=p.get_float_arg(2, 0.1);
    }

    void output(const Wave *wave) const
    {
        cout<<fixed;
        cout.precision(6);

        float t=m_t0;
        while(t<m_t1){
            cout << t << "," << wave->evaluate(t) << endl;
            t += m_dt;
        }
    }
};

#endif
