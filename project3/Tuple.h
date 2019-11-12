//this will hold a vector of strings.
#pragma once
#include<vector>
#include<string>
using namespace std;
class Tuple : public vector<string> //this will
{
private:
    /* data */
public:
    using vector::push_back; //specify which vect funcitons you are using
    using vector::at;
    using vector::erase;
    Tuple(/* args */);
    ~Tuple();
};

