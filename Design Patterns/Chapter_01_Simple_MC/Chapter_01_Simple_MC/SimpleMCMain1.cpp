//
//  SimpleMcMain1.cpp
//  Sandbox-Cpp
//
//  Created by Dialid Santiago on 31/01/2021.
//

#include "SimpleMCMain1.hpp"
#include "Random1.hpp"
#include <iostream>
#include <cmath>

using namespace std;

double SimpleMonteCarlo1(double Expiry, // T
                         double Strike, // K
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
        double thisPayOff = thisSpot - Strike;
        thisPayOff = thisPayOff > 0 ? thisPayOff : 0;
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
    cout << "\nEnter expiry T: \n";
    cin >> Expiry;
    
    cout << "\nEnter Strike K:\n";
    cin >> Strike;
    
    cout << "\nEnter spot S0:\n";
    cin >> Spot;
    
    cout << "\nEnter vol sigma:\n";
    cin >> Vol;
    
    cout << "\nEnter r\n";
    cin >> r;
    
    cout << "\nNumber of paths\n";
    cin >> NumberOfPath;
    
    double result = SimpleMonteCarlo1(Expiry,
                                      Strike,
                                      Spot,
                                      Vol,
                                      r,
                                      NumberOfPath);
    cout << "The price is "<< result << "\n";
    cout << "Enter any string to terminate the process and hit Enter. " << "\n";
    double tmp;
    cin >>tmp;

    return 0;


}
