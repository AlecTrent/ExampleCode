// File name: Wheat.h
// Author: Alec Trent
// Student ID: U766E384
// Assignment Number: 7

#ifndef WHEAT_H_
#define WHEAT_H_

#include <string>

#include "Grain.h"

/**
 * The Wheat class hold some basic properties of wheat, such as Average Test Weight and Ideal Moisture Level
 */

class Wheat : public Grain {
public:
   // Default constructor
   Wheat();
   
   //Overloaded constructor
   Wheat(double moistureLevel, double foreignMaterial);
   
   // Clone function
   Wheat* clone();
   
   // Returns a string containing the type of grain
   virtual std::string getType() const;
   
   // Returns the average test weight
   virtual const double getAverageTestWeight() const;
   
   // Returns the ideal moisture level
   virtual const double getIdealMoistureLevel() const;
};

#endif
