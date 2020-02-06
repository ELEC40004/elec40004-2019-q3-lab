#ifndef factory_parameters_hpp
#define factory_parameters_hpp

#include <string>
#include <cassert>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>

using namespace std;

/*
    Represents a heirarchical set of parameters.
    
    Each parameter set consists of:
    - A verb
    - zero or more arguments, held as a vector of factory_parameters:
      - a "string" : a parameter set with no arguments
      - a sub-parameter : a parameter set with at least one argument

    Some examples would be:
    - "x" : the single verb x
    - "[y 0 1]" : a verb y with parameters "0" and "1"
    - "[x 0.4 [y 5]]" : a verb x with parameters "0.4" and ["y" "5"] 
*/
struct factory_parameters
{
    string verb;
    vector<factory_parameters> args;

    string get_string_arg(int index, const std::string &defaultValue) const
    {
        if(index>=args.size()){
            return defaultValue;
        }
        if(args[index].args.size()>0){
            // TODO  : Better error handling
            cerr<<" Expected string argument, but got a composite argument " << endl;
            exit(1);
        }
        return args[index].verb;
    }

    float get_float_arg(int index, float defaultValue) const
    {
        return stof(get_string_arg(index, to_string(defaultValue)));
    }
};

// Reads factory parameters from a stream
/*
    Parameters are described using strings of the form:
    - "verb" ->   {"verb", {}}
    - "[verb]" -> {"verb", {}}
    - "[verb arg1]" -> {"verb, { {"arg1",{}} } }
    - "[verb arg1 arg2]" -> {"verb, { { {"arg1",{}} , {"arg2",{}} } }
    - "[verb [arg1] arg2]" -> {"verb, { { {"arg1",{}} , {"arg2",{}} } }
*/
istream &operator>>(istream &src, factory_parameters &p);

ostream &operator<<(ostream &src, const factory_parameters &p);

// Reads factory parameters from a string
factory_parameters parse_factory_parameters(const string &spec);

/* Prints the factory parameters out using the given level of indent */
string to_string(const factory_parameters &p, const string &indent);
string to_string(const factory_parameters &p);

#endif
