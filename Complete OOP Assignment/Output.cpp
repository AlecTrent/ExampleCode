// File name: Output.cpp
// Author: Alec Trent
// Student ID: U766E384
// Assignment Number: 7

#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdexcept>

#include "Output.h"
#include "Ticket.h"

void Output::outputTickets(const ContainerTemplate::Array<Ticket>& tickets)
{
   // If there was no tickets entered, notify the user and proceed to exit
   if (tickets.size() == 0) {
      std::cout << "No tickets entered. ";
   } else {
      // Sets the output to two decimal places
      std::cout << std::fixed;
      std::cout << std::setprecision(2);
   
      // A for loop is useful for iterating through each ticket in the Array
      // Another condition for the Array being empty is here as well, so that we don't read garbage data
      for (int i = 0; i < (int) tickets.size(); i++) {
         // Output all the data from the ticket
         std::cout << tickets[i];
      }
   }
}

void Output::outputSummary(const ContainerTemplate::Array<Ticket>& tickets)
{
   // If there was no tickets entered, notify the user and proceed to exit
   if (tickets.size() == 0) {
      std::cout << "No tickets entered. ";
   } else {
      // Sets the output to two decimal places
      std::cout << std::fixed;
      std::cout << std::setprecision(2);
      
      // These values will be used at the end for printing total gross bushels and total net bushels
      double totalGrossBushels = 0;
      double totalNetBushels = 0;      
      
      // We're using the same for loop setup as the function above
      for (int i = 0; i < (int) tickets.size(); i++) {
         // Adding the gross bushels and net bushels for this ticket
         totalGrossBushels += tickets[i].getGrossBushels();
         totalNetBushels += tickets[i].getNetBushels();
      }
      
      // Outputs the final bit of data required, total net bushels, and total gross bushels
      std::cout << "Harvest Summary Totals: " << std::endl;
      std::cout << "    " << totalGrossBushels << "  Gross Bushels" << std::endl;
      std::cout << "    " << totalNetBushels << "  Net Bushels" << std::endl << std::endl;
   }
}

void Output::writeTicketsToFile(const ContainerTemplate::Array<Ticket>& tickets)
{
   try {
      // Open a file pointer to write to HarvestTicketReceipts.txt, clearing any data in there
      std::ofstream outFile;
      
      // Set up outFile to throw exceptions for badbit
      outFile.exceptions(std::ifstream::badbit);
      outFile.open("HarvestTicketReceipts.txt", std::ios::trunc);
      
      // Output the header line first
      outFile << tickets[0].returnHeader() << std::endl;
      
      for (unsigned int i = 0; i < tickets.size(); i++)
         outFile << tickets[i].returnFieldedData() << std::endl;
         
      outFile.close();
   }
   
   // If the file could not be opened for some reason
   catch (const std::ios_base::failure& badFile) {
      std::cout << "HarvestTicketReceipts.txt could not be opened." << std::endl;
   }
}
