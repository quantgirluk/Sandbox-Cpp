//
//  SimpleMcMain1.cpp
//  Sandbox-Cpp
//
//  Created by Dialid Santiago on 02/02/2021.
//

#include "SimpleMCMain1.hpp"
#include "Random.hpp"
#include "PayOff.hpp"
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double SimpleMonteCarlo(const PayOff& thePayOff,
                         double Expiry, // T
                         double Spot, // S0
                         double Vol, // sigma
                         double r, // r
                         unsigned long NumberOfPaths
                         )
{

    double variance = Vol*Vol*Expiry;
    double rootVariance = sqrt(variance);
    double itoCorrection = -0.5*variance;
    
    double movedSpot = Spot*exp(r*Expiry + itoCorrection);
    double thisSpot;
    double runningSum = 0;
    
    for (unsigned long i=0; i<NumberOfPaths; i++) {
        double thisGaussian = GetOneGaussianByBoxMuller();
        thisSpot   = movedSpot*exp(rootVariance*thisGaussian);
        double thisPayOff = thePayOff(thisSpot);
        runningSum += thisPayOff;
    }
    
    double mean = runningSum / NumberOfPaths;
    mean *= exp(-r*Expiry);
    return mean;
}


int main()
{
    double Expiry;
    double Strike;
    double Spot;
    double Vol;
    double r;
    unsigned long NumberOfPath;
    
    //read in parameters
    cout << "\nEnter Expiry T:";
    cin >> Expiry;
    
    cout << "\nEnter Strike K:";
    cin >> Strike;
    
    cout << "\nEnter Spot S0:";
    cin >> Spot;
    
    cout << "\nEnter Volatility:";
    cin >> Vol;
    
    cout << "\nEnter Interest Rate r:";
    cin >> r;
    
    cout << "\nNumber of MC paths:";
    cin >> NumberOfPath;
    
    PayOff callPayOff(Strike, PayOff::call);
    PayOff putPayOff(Strike, PayOff::put);
    
    double resultCall = SimpleMonteCarlo(callPayOff,Expiry, Spot, Vol, r, NumberOfPath);
    double resultPut = SimpleMonteCarlo(putPayOff,Expiry, Spot, Vol, r, NumberOfPath);

    
    cout << "The Prices are:\n"<< setprecision(3) <<resultCall << " for the Call\n";
    cout << setprecision(3) << resultPut<< " for the Put\n";
    double tmp;
    cin >>tmp;

    return 0;


}
