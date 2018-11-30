// File name: Output.h
// Author: Alec Trent
// Student ID: U766E384
// Assignment Number: 7

#ifndef OUTPUT_H_
#define OUTPUT_H_

#include "Array.h"
#include "Ticket.h"

/**
 * The Output class allows output of various values to the console
 */
class Output {
public:
	// Output Array of tickets
	static void outputTickets(const ContainerTemplate::Array<Ticket>& tickets);

	// Output summary of totals for Array of tickets
	static void outputSummary(const ContainerTemplate::Array<Ticket>& tickets);
	
	// Outputs the tickets to a file
	static void writeTicketsToFile(const ContainerTemplate::Array<Ticket>& tickets);

private:
	// Default constructor (use private to prevent creation)
	Output();
};

#endif /* OUTPUT_H_ */
