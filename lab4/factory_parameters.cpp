#include "factory_parameters.hpp"

// Helper function to skip whitespace then peek at character
int peek_skip_ws(istream &src)
{
    return (src >> ws).peek();
}

istream &operator>>(istream &src, factory_parameters &p)
{
    assert(!src.fail());
    if( peek_skip_ws(src) =='['){
        char tmp;
        src>>tmp; // consume the '('
        
        src>>p.verb; // consume the verb
        
        while( (src >> ws).peek() != ']'){
            factory_parameters part;
            src>>part;
            p.args.push_back( part );
        }
        
        assert( peek_skip_ws(src) == ']');
        src>>tmp; // consume the ')'
    }else{
        src>>p.verb;
    }

    if(p.verb.find('[') != string::npos || p.verb.find(']') != string::npos){
        cerr<<"factory_parameters:Error - found '[' or ']' in string '"<<p.verb<<"'. Use spaces between brackets.\n";
        exit(1);
    }

    return src;
}

factory_parameters parse_factory_parameters(const string &spec)
{
    stringstream src(spec);
    factory_parameters res;
    src >> res;
    return res;
}

string to_string(const factory_parameters &f, const std::string &indent)
{
    if(f.args.empty()){
        return indent+f.verb;
    }else{
        string res=indent+"( "+f.verb + "\n";
        for(int i=0; i<f.args.size(); i++){
            res=res+indent+to_string( f.args[i], indent+"  " ) + "\n";
        }
        res=res+indent+")";
        return res;
    }
}

string to_string(const factory_parameters &f)
{
    return to_string(f, "");
}

ostream &operator<<(ostream &dst, const factory_parameters &p)
{
    dst << to_string(p);
    return dst;
}