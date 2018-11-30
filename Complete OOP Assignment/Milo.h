// File name: Milo.h
// Author: Alec Trent
// Student ID: U766E384
// Assignment Number: 7

#ifndef MILO_H_
#define MILO_H_

#include <string>

#include "Grain.h"

/**
 * The Milo class hold some basic properties of grain sorghum, such as Average Test Weight and Ideal Moisture Level
 */

class Milo : public Grain {
public:
   // Default constructor
   Milo();
   
   //Overloaded constructor
   Milo(double moistureLevel, double foreignMaterial);
   
   // Clone function
   Milo* clone();
   
   // Returns a string containing the type of grain
   virtual std::string getType() const;
   
   // Returns the average test weight
   virtual const double getAverageTestWeight() const;
   
   // Returns the ideal moisture level
   virtual const double getIdealMoistureLevel() const;
};

#endif
