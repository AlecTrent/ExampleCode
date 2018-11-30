// File name: Soybean.h
// Author: Alec Trent
// Student ID: U766E384
// Assignment Number: 7

#ifndef SOYBEAN_H_
#define SOYBEAN_H_

#include <string>

#include "Grain.h"

/**
 * The Soybean class hold some basic properties of soybeans, such as Average Test Weight and Ideal Moisture Level
 */

class Soybean : public Grain {
public:
   // Default constructor
   Soybean();
   
   //Overloaded constructor
   Soybean(double moistureLevel, double foreignMaterial);
   
   // Clone function
   Soybean* clone();
   
   // Returns a string containing the type of grain
   virtual std::string getType() const;
   
   // Returns the average test weight
   virtual const double getAverageTestWeight() const;
   
   // Returns the ideal moisture level
   virtual const double getIdealMoistureLevel() const;
};

#endif
