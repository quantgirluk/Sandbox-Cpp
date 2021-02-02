//
//  PayOff.cpp
//  Exercises
//
//  Created by Dialid Santiago on 02/02/2021.
//

#include "PayOff.hpp"
#include <algorithm>
using namespace std;

PayOff::PayOff(double Strike_, OptionType TheOptionType_)
:
    Strike(Strike_),TheOptionType(TheOptionType_)
{
}

double PayOff::operator()(double Spot) const
{
    switch (TheOptionType)
    {
        case call:
            return max(Spot - Strike, 0.0);
        case put:
            return max(Strike - Spot,0.0);
            
        default:
            throw("unknow option type found.");
    }
}
