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

double SimpleMonteCarlo1(double Expiry,
                         double Strike,
                         double Spot,
                         double Vol,
                         double r,
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
    cout << "\nEnter expiry\n";
    cin >> Expiry;
    
    cout << "\nEnter Strike\n";
    cin >> Strike;
    
    cout << "\nEnter spot\n";
    cin >> Spot;
    
    cout << "\nEnter vol\n";
    cin >> Vol;
    
    cout << "\nEnter r\n";
    cin >> r;
    
    cout << "\n Number of paths\n";
    cin >> NumberOfPath;
    
    double result = SimpleMonteCarlo1(Expiry,
                                      Strike,
                                      Spot,
                                      Vol,
                                      r,
                                      NumberOfPath);
    cout << "the price is "<< result << "\n";
    
    double tmp;
    cin >>tmp;

    return 0;


}
