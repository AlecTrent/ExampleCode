// File name: Grain.h
// Author: Alec Trent
// Student ID: U766E384
// Assignment Number: 7

#ifndef GRAIN_H_
#define GRAIN_H_

#include <string>

/**
 * The Grain class identifies properties of a sample of grain
 */
class Grain {
public:
	// Constructor default
	Grain();

	// Constructor allowing caller to specify sample's moisture level (%) and foreign material (%)
	Grain(double moistureLevel, double foreignMaterial);

	// Destructor
	virtual ~Grain();
	
	// Pure-virtual Clone function that returns a clone of the grain object
	virtual Grain* clone() = 0;
	
	// Pure-virtual function that returns child object type
	virtual std::string getType() const = 0;

	// Pure-virtual accessor to return grain's average test weight (lbs/bushel)
	virtual const double getAverageTestWeight() const = 0;

	// Pure-virtual accessor to return grain's ideal moisture level (percent)
	virtual const double getIdealMoistureLevel() const = 0;

	// Accessor to return sample's moisture level (percent)
	double getMoistureLevel() const;

	// Accessor to return sample's foreign material (percent)
	double getForeignMaterial() const;
	
	// Returns a string representing the calling object's grain type
   std::string toString();

private:
	// Member variables
	double moistureLevel;
	double foreignMaterial;
};

#endif /* GRAIN_H_ */
