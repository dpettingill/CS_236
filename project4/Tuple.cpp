#include "Tuple.h"

Tuple::Tuple(/* args */){}
Tuple::~Tuple() {}

string Tuple::toString(Tuple my_header) {
    stringstream ss;
    int i = 0;
    for(Tuple::iterator it = this->begin(); it != this->end(); ++it) {
        if (it == this->begin()) ss << "  ";
        if (it+1 < this->end()) {
            ss << my_header.at(i) << "=" << this->at(i) << ", "; // of the form N='12345'
            i++;
        }                 
        else ss << my_header.at(i) << "=" << this->at(i) << "\n";
    }
    i = 0; //reset i
    return ss.str();
}