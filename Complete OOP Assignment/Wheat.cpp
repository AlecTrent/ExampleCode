// File name: Wheat.cpp
// Author: Alec Trent
// Student ID: U766E384
// Assignment Number: 7

#include <string>

#include "Wheat.h"

// Unnamed namespace used to store constants
namespace 
{
   const double AVERAGE_TEST_WEIGHT = 60.0;
   const double IDEAL_MOISTURE_LEVEL = 13.5;
}

// Constructor allowing caller to specify sample's moisture level (%) and foreign material (%)
Wheat::Wheat(double moistureLevel, double foreignMaterial): Grain(moistureLevel, foreignMaterial)
{
   
}

// Default constructor overloading the constructor with arguments
Wheat::Wheat(): Grain(0,0)
{
   
}

// Cloning function, creates a new object of same type in dynamic memory
Wheat* Wheat::clone()
{
   Wheat* cloneWheat = new Wheat(Grain::getMoistureLevel(), Grain::getForeignMaterial());
   return cloneWheat;
}

// Returns a string containing the type of grain
std::string Wheat::getType() const
{
   return "Wheat";
}
   
// Returns the average test weight
const double Wheat::getAverageTestWeight() const
{
   return AVERAGE_TEST_WEIGHT;
}
   
// Returns the ideal moisture level
const double Wheat::getIdealMoistureLevel() const
{
   return IDEAL_MOISTURE_LEVEL;
}
