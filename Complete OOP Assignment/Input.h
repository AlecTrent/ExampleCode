// File name: Input.h
// Author: Alec Trent
// Student ID: U766E384
// Assignment Number: 7

#ifndef INPUT_H_
#define INPUT_H_

#include "Array.h"
#include "Ticket.h"

/**
 * The Input class allows input of various values from the console
 */
class Input {
public:
	// Return Array of tickets (prompt user for tickets, adding each to Array of tickets)
	static void inputTickets(ContainerTemplate::Array<Ticket>& tickets);
	
	// Read tickets from a provided file, HarvestTickets.txt
	static bool readTicketsFromFile(ContainerTemplate::Array<Ticket>& tickets);
	
	// Helper function to remove spaces from the string given to it
	static std::string removeSpaces(std::string inputString);

private:
	// Default constructor (use private to prevent creation)
	Input();
};

#endif /* INPUT_H_ */
