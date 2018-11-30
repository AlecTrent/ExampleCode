// File name: Grain.cpp
// Author: Alec Trent
// Student ID: U766E384
// Assignment Number: 7

#include "Grain.h"

// Constructor allowing caller to specify sample's moisture level (%) and foreign material (%)
Grain::Grain(double moistureLevel, double foreignMaterial): moistureLevel(moistureLevel), foreignMaterial(foreignMaterial) 
{
   
}

// Default constructor overloading the constructor with arguments
Grain::Grain(): moistureLevel(0), foreignMaterial(0)
{
   
}

// Destructor
Grain::~Grain()
{

}

// Accessor functions
// Returns the sample's moisture level
double Grain::getMoistureLevel() const
{
   return moistureLevel;
}

// Return's the sample's foreign material content
double Grain::getForeignMaterial() const
{
   return foreignMaterial;
}

// Returns a string containing the calling object's grain type

std::string Grain::toString()
{
   return getType();
}

