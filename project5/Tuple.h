//this will hold a vector of strings.
#pragma once
#include<vector>
#include<string>
#include<iostream>
#include<sstream>
using namespace std;
class Tuple : public vector<string> //this will
{
private:
    /* data */
public:
    using vector::push_back; //specify which vect funcitons you are using
    using vector::at;
    using vector::erase;
    std::string toString(Tuple my_header);
    Tuple(/* args */);
    ~Tuple();
};

