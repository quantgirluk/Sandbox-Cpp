//
//  PayOff.hpp
//  Exercises
//
//  Created by Dialid Santiago on 02/02/2021.
//

#ifndef PayOff_hpp
#define PayOff_hpp

#include <stdio.h>

class PayOff
{
public:
    enum OptionType {call, put, digital};
    PayOff(double Strike_, OptionType TheOptionType_); // Constructor
    double operator()(double Spot) const; // Main Method - given a value of a spot, return the value of the payoff
    //Note that operator() is defined as const, this means that method would not modify the object

private:
    double Strike;
    OptionType TheOptionType;
};


#endif /* PayOff_hpp */
