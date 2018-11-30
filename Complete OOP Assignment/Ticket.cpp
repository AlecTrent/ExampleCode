// File name: Ticket.cpp
// Author: Alec Trent
// Student ID: U766E384
// Assignment Number: 7

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <ctime>

#include "Ticket.h"
#include "Grain.h"

// Constructors
// Overloaded constructor, handles for if the pointer being passed in is a nullptr
Ticket::Ticket(const std::string& number, const int grossWeight, const int tareWeight, Grain* grainSample):
   number(number), grossWeight(grossWeight), tareWeight(tareWeight)
{
   time(&timestamp);
   
   if (grainSample != nullptr)
      sample = grainSample->clone();
   else
      sample = nullptr;
}

// Overloaded constructor to allow passing in a struct tm to copy to timestamp, a time_t
Ticket::Ticket(struct tm timeStruct, const std::string& number, const int grossWeight, const int tareWeight, Grain* grainSample):
   number(number), grossWeight(grossWeight), tareWeight(tareWeight)
{
   timestamp = mktime(&timeStruct);
   
   if (grainSample != nullptr)
      sample = grainSample->clone();
   else
      sample = nullptr;
}

// Constructor with no arguments, initializes all number values to 0, number to an empty string, and sample to nullptr
Ticket::Ticket(): number(""), grossWeight(0), tareWeight(0), sample(nullptr)
{
   timestamp = 0;
}

// Copy constructor
Ticket::Ticket(const Ticket& ticketCopy)
{
   // Set all the values equal
   number = ticketCopy.number;
   grossWeight = ticketCopy.grossWeight;
   tareWeight = ticketCopy.tareWeight;
   timestamp = ticketCopy.timestamp;
   
   // Clone the grain pointer if it's not nullptr
   if (ticketCopy.sample != nullptr)
      sample = ticketCopy.sample->clone();
   else
      sample = nullptr;
}

// Destructor
Ticket::~Ticket()
{
   // If the pointer is not null, delete it. Otherwise, continue
   if (sample != nullptr)
      delete sample;
}

// Accessor Functions
// Returns the timestamp
std::time_t Ticket::getTimestamp() const
{
   return timestamp;
}

// Returns the Ticket ID
std::string Ticket::getNumber() const
{
   return number;
}

// Returns the gross weight of the truck
int Ticket::getGrossWeight() const
{
   return grossWeight;
}

// Returns the tare (empty) weight of the truck
int Ticket::getTareWeight() const
{
   return tareWeight;
}

// Returns a clone of the grain sample object if it exists. Otherwise, return nullptr
Grain* Ticket::getSample() const
{
   if (sample != nullptr)
      return sample->clone();
   else
      return nullptr;
}

// Returns the net weight of the load
int Ticket::getNetWeight() const
{
   return grossWeight - tareWeight;
}

// Returns the gross bushels, using a constant to determine the amount
double Ticket::getGrossBushels() const
{  
   if (sample != nullptr)
      return getNetWeight() / sample->getAverageTestWeight();
   else
      return 0;
}

// Returns the amount to dock based on moisture level
// If the moisture level is less than 12%, this has no impact. If it's greater than 12%, then moisture dockage is calculated
double Ticket::getMoistureLevelDockage() const
{  
   if (sample != nullptr) {
      if (sample->getMoistureLevel() <= sample->getIdealMoistureLevel())
         return 0;
      else
         return getGrossBushels() * ((sample->getMoistureLevel() - sample->getIdealMoistureLevel()) / 100);
   } else {
      return 0;
   }
}

// This simply calculates the amount to dock based on how much foreign material there is
// There's no conditions here, just a straight calculation
double Ticket::getForeignMaterialDockage() const
{
   if (sample != nullptr)
      return getGrossBushels() * (sample->getForeignMaterial() / 100);
   else
      return 0;
}

// This returns net bushels after moisture and foreign material dockages have been taken out of the net bushels
double Ticket::getNetBushels() const
{
   return (getGrossBushels() - getMoistureLevelDockage() - getForeignMaterialDockage());
}

// This function returns a string of header data for the output file
std::string Ticket::returnHeader() const
{
   return "Type|Date|Time|Number|GrossWeight|TareWeight|NetWeight|GrossBushels|MoistureLevel|MoistureLevelDockage|ForeignMaterial|ForeignMaterialDockage|NetBushels";
}

std::string Ticket::returnFieldedData() const
{
   // First we initialize a stringstream pointer. This makes formatting the string much easier
   std::stringstream ss;
   
   // Set the decimal precision of ss to two decimal places
   ss.precision(2);
   
   // Converts the time from a raw int to a tm object. This makes outputting time much easier
   struct tm* timeInfo = std::localtime(&timestamp);
   
   // Store the formatted time we want in a C-String
   char dateString[8+1];
   char timeString[6+1];
   
   strftime(dateString, 8+1, "%Y%m%d", timeInfo);
   strftime(timeString, 6+1, "%H%M%S", timeInfo);
   
   // Final checks to see if sample is nullptr or not
   std::string grainType;
   double moistureLevel, foreignMaterial;
   
   if (sample != nullptr) {
      grainType = sample->toString();
      moistureLevel = sample->getMoistureLevel();
      foreignMaterial = sample->getForeignMaterial();
   } else {
      grainType = "";
      moistureLevel = 0;
      foreignMaterial = 0;
   }
   
   // Now we can pipe anything we want into ss. Fixed is used to set it to decimal notation instead of scientific
   // std::put_time is in the <iomanip> library, and the %c token allows input exactly as requested
   ss << std::fixed << grainType << "|" << dateString << "|" << timeString << "|" << number << "|" << grossWeight << "|" << tareWeight << "|"
      << getNetWeight() << "|" << getGrossBushels() << "|" << moistureLevel << "|" << getMoistureLevelDockage() << "|"
      << foreignMaterial << "|" << getForeignMaterialDockage() << "|" << getNetBushels();
   
   return ss.str();
}

// This returns a string containing all of the data in the class, formatted
std::string Ticket::toString() const
{
   // First we initialize a stringstream pointer. This makes formatting the string much easier
   std::stringstream ss;
   
   // Set the decimal precision of ss to two decimal places
   ss.precision(2);
   
   // Converts the time from a raw int to a tm object. This makes outputting time much easier
   struct tm* timeInfo = std::localtime(&timestamp);
   
   // Store the formatted time we want in a C-String
   char timeString[19+1];
   strftime(timeString, 19+1, "%m/%d/%Y %H:%M:%S", timeInfo);

   // Final checks to see if sample is nullptr or not
   std::string grainType;
   double moistureLevel, foreignMaterial;

   if (sample != nullptr) {
      grainType = sample->toString();
      moistureLevel = sample->getMoistureLevel();
      foreignMaterial = sample->getForeignMaterial();
   } else {
      grainType = "";
      moistureLevel = foreignMaterial = 0;
   }
   
   // Now we can pipe anything we want into ss. Fixed is used to set it to decimal notation instead of scientific
   // std::put_time is in the <iomanip> library, and the %c token allows input exactly as requested
   ss << std::fixed << "  " << grainType <<  " Ticket " << number << " - " << timeString
      << ":\n    " << grossWeight << "  Gross Weight\n    " << tareWeight << "  Tare Weight \n    " << getNetWeight() << "  Net Weight\n\n    "
      << getGrossBushels() << "  Gross Bushels\n    " << getMoistureLevelDockage() << "    Moisture Level (" << moistureLevel << "%)\n    "
      << getForeignMaterialDockage() << "    Foreign Material (" << foreignMaterial << "%)\n    " << getNetBushels() << "  Net Bushels\n    " << "\n\n";
   
   return ss.str();
}

// Sorts types such that Wheat < Soybean < Milo
bool Ticket::sortTypes(const Ticket& ticket1, const Ticket& ticket2)
{  
   // Check to be sure if both tickets are pointing to valid sample objects
   if (ticket1.sample == nullptr || ticket2.sample == nullptr)
      return false;
   
   // Assign some integers to store type "values"
   int type1, type2;
   
   // Figure out what the first type's "value" is; 0 for Wheat, 1 for Soybean, 2 for Milo
   if (ticket1.sample->toString() == "Wheat")
      type1 = 0;
   else if (ticket1.sample->toString() == "Soybean")
      type1 = 1;
   else
      type1 = 2;
      
   // Now determine the second type's "value"
   if (ticket2.sample->toString() == "Wheat")
      type2 = 0;
   else if (ticket2.sample->toString() == "Soybean")
      type2 = 1;
   else
      type2 = 2;
   
   // Now do the actual comparison
   // First we check to see if the type is greater than or less than the other, returning true/false respectively
   if (type1 < type2) {
      return true;
   } else if (type2 < type1) {
      return false;
   } else {
      // This is if they are the same type, in which case we sort by net bushels, high to low
      if (ticket1.getNetBushels() > ticket2.getNetBushels()) {
         return true;
      } else {
         return false;
      }
   }
}

// The overloaded assignment operator sets one Ticket object equal to another
const Ticket& Ticket::operator =(const Ticket& ticketCopy)
{
   // If the two Ticket objects are equal, return the pointer to the ticket object
   if (this == &ticketCopy) {
      return *this;
   } else {
      // Set all the values equal
      number = ticketCopy.number;
      grossWeight = ticketCopy.grossWeight;
      tareWeight = ticketCopy.tareWeight;
      timestamp = ticketCopy.timestamp;
      
      // Delete the current grain sample if it's not nullptr
      if (sample != nullptr)
         delete sample;
      
      // Clone the grain pointer if the pointer is not nullptr
      if (ticketCopy.sample != nullptr)
         sample = ticketCopy.sample->clone();
      else
         sample = nullptr;
      
      return *this;
   }
}

// The overloaded equality operator returns true if the string names are the same, and false if not
bool Ticket::operator ==(const Ticket& ticket) const
{
   return (number == ticket.number);
}

// The overloaded less than operator returns true if the left ticket's net bushels is less than the right ticket's. Otherwise, false.
bool Ticket::operator <(const Ticket& ticket) const
{
   return (this->getNetBushels() < ticket.getNetBushels());
}

// The overloaded insertion operator uses toString to output the data from the ticket object directly to something like cout
// Since it is a friend function, we don't need Ticket::.
std::ostream& operator <<(std::ostream& os, const Ticket& tickets)
{
   os << tickets.toString();
   
   return os;
}
