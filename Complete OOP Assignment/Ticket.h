// File name: Ticket.h
// Author: Alec Trent
// Student ID: U766E384
// Assignment Number: 7

#ifndef TICKET_H_
#define TICKET_H_

#include <ctime>
#include <ostream>
#include <string>

#include "Grain.h"

/**
 * The Ticket class identifies properties of a ticket
 **/
class Ticket {
public:
	// Constructor allowing caller to specify a ticket's number,
	//  gross weight (lbs), tare weight (lbs), and grain sample
	Ticket(const std::string& number, const int grossWeight, const int tareWeight, Grain* grainSample);
	
	// Constructor allowing the user to pass in a timestamp
	Ticket(struct tm timeStruct, const std::string& number, const int grossWeight, const int tareWeight, Grain* grainSample);
	
	// Constructor default
	Ticket();
	
	// Copy constructor
	Ticket(const Ticket& ticketCopy);
	
	// Destructor
	~Ticket();

	// Accessor to return timestamp
	std::time_t getTimestamp() const;

	// Accessor to return number
	std::string getNumber() const;

	// Accessor to return gross weight (lbs)
	int getGrossWeight() const;

	// Accessor to return tare weight (lbs)
	int getTareWeight() const;
	
	// Pseudo-accessor to return a clone of the Grain sample object
	Grain* getSample() const;

	// Function to return net weight (lbs)
	int getNetWeight() const;

	// Function to return gross bushels (lbs)
	double getGrossBushels() const;

	// Function to return moisture level dockage (lbs bushels)
	double getMoistureLevelDockage() const;

	// Function to return foreign material dockage (lbs bushels)
	double getForeignMaterialDockage() const;

	// Function to return net bushels (lbs)
	double getNetBushels() const;
	
	// Returns a formatted header string
	std::string returnHeader() const;
	
	// Returns a string of the same format as the header
	std::string returnFieldedData() const;

	// Returns a string representing ticket's attributes (in form of a receipt)
	std::string toString() const;
	
	// Sorts types such that Wheat < Soybean < Milo, further sorts by net bushels, high to low
	// Static because std::sort requires a function pointer
	static bool sortTypes(const Ticket& ticket1, const Ticket& ticket2);
	
	// Overloaded assignment operator =
	const Ticket& operator =(const Ticket& ticketCopy);

	// Overloaded equality operator ==
	bool operator ==(const Ticket& ticket) const;
	
	// Overloaded less than operator <
	bool operator <(const Ticket& ticket) const;

	// Overloaded insertion operator <<
	friend std::ostream& operator <<(std::ostream& os, const Ticket& tickets);	

private:
	// Member variables
	std::time_t timestamp;
	std::string number;
	int grossWeight;
	int tareWeight;
	Grain* sample;
};

#endif /* TICKET_H_ */
