// File name: Milo.cpp
// Author: Alec Trent
// Student ID: U766E384
// Assignment Number: 7

#include <string>

#include "Milo.h"

// Unnamed namespace used to store constants
namespace 
{
   const double AVERAGE_TEST_WEIGHT = 56.0;
   const double IDEAL_MOISTURE_LEVEL = 13.0;
}

// Constructor allowing caller to specify sample's moisture level (%) and foreign material (%)
Milo::Milo(double moistureLevel, double foreignMaterial): Grain(moistureLevel, foreignMaterial)
{
   
}

// Default constructor overloading the constructor with arguments
Milo::Milo(): Grain(0,0)
{
   
}

// Cloning function, creates a new object of same type in dynamic memory
Milo* Milo::clone()
{
   return new Milo(Grain::getMoistureLevel(), Grain::getForeignMaterial());
}

// Returns a string containing the type of grain
std::string Milo::getType() const
{
   return "Grain Sorghum";
}
   
// Returns the average test weight
const double Milo::getAverageTestWeight() const
{
   return AVERAGE_TEST_WEIGHT;
}
   
// Returns the ideal moisture level
const double Milo::getIdealMoistureLevel() const
{
   return IDEAL_MOISTURE_LEVEL;
}
