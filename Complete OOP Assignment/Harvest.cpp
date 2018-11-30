// File name: Harvest.cpp
// Author: Alec Trent
// Student ID: U766E384
// Assignment Number: 7

#include <iostream>
#include <algorithm> // std::sort

#include "Input.h"
#include "Output.h"

int main(void) 
{
   // Declaring the Tickets object to hold our Array of tickets in
   ContainerTemplate::Array<Ticket> ticketArray;
   
   // Input and output handled by functions of their own classes
   Input::readTicketsFromFile(ticketArray);
   Input::inputTickets(ticketArray);
   
   // Sort the tickets using std::sort and the iterators
   // We're using the extra credit way of sorting (high to low, and by grain types)
   std::sort(ticketArray.begin(), ticketArray.end(), Ticket::sortTypes);
   
   // Output the tickets to screen and to file
   Output::outputTickets(ticketArray);
   Output::outputSummary(ticketArray);
   Output::writeTicketsToFile(ticketArray);
   
   // This is a dummy variable used to handle the exit routine
   std::string exit;
   std::cout << "Press enter to exit.";
   
   // Flushes the input buffer so we can read output
   std::cin.ignore();
   getline(std::cin,exit);
   
   return 0;
}
