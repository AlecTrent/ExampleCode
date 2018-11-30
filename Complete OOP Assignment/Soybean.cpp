// File name: Soybean.cpp
// Author: Alec Trent
// Student ID: U766E384
// Assignment Number: 7

#include <string>

#include "Soybean.h"

// Unnamed namespace used to store constants
namespace 
{
   const double AVERAGE_TEST_WEIGHT = 60.0;
   const double IDEAL_MOISTURE_LEVEL = 13.0;
}

// Constructor allowing caller to specify sample's moisture level (%) and foreign material (%)
Soybean::Soybean(double moistureLevel, double foreignMaterial): Grain(moistureLevel, foreignMaterial)
{
   
}

// Default constructor overloading the constructor with arguments
Soybean::Soybean(): Grain(0,0)
{
   
}

// Cloning function, creates a new object of same type in dynamic memory
Soybean* Soybean::clone()
{
   Soybean* cloneGrain = new Soybean(Grain::getMoistureLevel(), Grain::getForeignMaterial());
   return cloneGrain;
}

// Returns a string containing the type of grain
std::string Soybean::getType() const
{
   return "Soybean";
}
   
// Returns the average test weight
const double Soybean::getAverageTestWeight() const
{
   return AVERAGE_TEST_WEIGHT;
}
   
// Returns the ideal moisture level
const double Soybean::getIdealMoistureLevel() const
{
   return IDEAL_MOISTURE_LEVEL;
}
