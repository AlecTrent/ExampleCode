// File name: Input.cpp
// Author: Alec Trent
// Student ID: U766E384
// Assignment Number: 7

#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdexcept>
#include <new>

#include "Input.h"
#include "Wheat.h"
#include "Soybean.h"
#include "Milo.h"

namespace {
   enum Type {WHEAT, SOYBEAN, MILO};
}

void Input::inputTickets(ContainerTemplate::Array<Ticket>& tickets)
{
   // Begin the loop to start inputting data
   // We'll use a boolean to determine whether the loop should continue or not
   bool loop = true;
   
   while (loop == true) {
      std::cout << "Please enter a ticket number, or enter the word 'end' to exit. ";
      
      // Data and flags to use in the constructor later on
      std::string stringTemp = "";
      std::string grainType = "";
      int intTemp = 0, intTemp2 = 0;
      double doubleTemp = 0, doubleTemp2 = 0;
      bool endFlag = false, repeatFlag = false;
      
      // Read in the text to be entered for the ticket name
      std::cin >> stringTemp;
      
      // If the empty string is entered, set the endFlag to true
      if (stringTemp == "end" || stringTemp == "End")
         endFlag = true;
      
      // If the string is either "end" or "End", then exit the loop
      if (endFlag == true) {
         loop = false;
      } else {
         // Begin the input block for the rest of the data
         std::cout << std::endl << "Gross weight (lbs): ";
         std::cin >> intTemp;
   
         std::cout << std::endl << "Tare weight (lbs): ";
         std::cin >> intTemp2;
   
         std::cout << std::endl << "Moisture level (%): ";
         std::cin >> doubleTemp;
   
         std::cout << std::endl << "Foreign material (%): ";
         std::cin >> doubleTemp2;
         
         std::cout << std::endl << "Grain Type: (W)heat, (S)oybean, or (G)rain Sorghum, defaults to Wheat: ";
         std::cin >> grainType;
         
         // Temporary pointer for whatever type we will be making
         Grain* grainTemp;
         
         if (grainType == "W" || grainType == "w")
            grainTemp = new Wheat(doubleTemp, doubleTemp2);
         else if (grainType == "S" || grainType == "s")
            grainTemp = new Soybean(doubleTemp, doubleTemp2);
         else if (grainType == "G" || grainType == "g")
            grainTemp = new Milo(doubleTemp, doubleTemp2);
         else
            grainTemp = new Wheat(doubleTemp, doubleTemp2);
            
         
         // Create the new Ticket object
         Ticket newTicket(stringTemp, intTemp, intTemp2, grainTemp);
         
         // This loop checks for repeat ticket names. If it is a repeat, don't add to the Array
         for (int i = 0; i < (int) tickets.size(); i++) {
            if (newTicket == tickets[i])
               repeatFlag = true;
         }
         
         // If the repeat flag is false, add it to the Array.
         if (repeatFlag == false) {
            tickets.add(newTicket);
            std::cout << "Ticket successfully added. " << std::endl << std::endl;
         } else {
            std::cout << "Ticket is a repeat. Ignored." << std::endl << std::endl;
         }
         
         // Free up the memory used by grainTemp
         delete grainTemp;
      }
   }
}


// This function will return true once the operation is completed
// False if for any reason the function is incompletable
bool Input::readTicketsFromFile(ContainerTemplate::Array<Ticket>& tickets)
{
   // Create an ifstream pointer and attempt to open the file
   // Also create a string to hold exceptions
   std::string exceptionString;
   std::ifstream readFile;
   
   // Set readFile to throw exceptions for badbit
   readFile.exceptions(std::ifstream::badbit);
   
   try {
      readFile.open("HarvestTickets.txt");
      
      // If the file is not found, throw a bad file exception
      if (!readFile.good())
         throw std::string("Bad file.");
   } 
   catch (std::string exceptionString) {
      std::cout << "HarvestTickets.txt does not exist within the current directory." << std::endl;
      return false;
   }
   
   // Initializing a line counter to help with error detection
   int lineCount = 0;
   
   // Start reading through the file until the end, discarding comment lines
   // This condition also handles for the file being empty
   while (!readFile.eof()) {
      try {
         // Increment our lineCount variable
         lineCount++;
         
         // Temporary holder string, assign it to the first getline
         std::string tempLine;
         std::getline(readFile, tempLine);
         
         // If the line is blank, continue
         if (tempLine == "" || tempLine == "\r")
            continue;
         
         // Flag to determine if the line is a comment or not
         bool commentLine = false;
         
         // If the first character is a comment symbol (#), simply continue.
         for (unsigned int i = 0; i < tempLine.length(); i++)
            if (tempLine[i] == '#')
               commentLine = true;
                        
         if (commentLine)
            continue;
         
         // Count the number of vertical bars. This will tell us how many fields we should be expecting
         // Any malformed fields as a result of improper vertical bars will be handled later on
         int verticalBars = 0;
         for (unsigned int i = 0; i <= tempLine.length(); i++)
            if (tempLine[i] == '|')
               verticalBars++;
         
         // If the number of vertical bars is not what is expected, throw an exception
         // The correct number of vertical bars as it stands is 7
         if (verticalBars != 7)
            throw std::string("Bad number of fields.");
         
         /*                Begin Processing Grain Type                   */
         // Start reading the first field, stopping at the first vertical bar
         std::string grainType = tempLine.substr(0,tempLine.find('|'));

         // Use the removeSpaces function to delete the spaces
         grainType = Input::removeSpaces(grainType);
         
         // If the string is "AllSpaces", throw an exception
         if (grainType == "AllSpaces")
            throw std::string("Grain type field contains only spaces or is empty.");
         
         // If the grainType is not one of the known ones, throw a BAD_TYPE exception
         // Setting the string to lowercase to resolve issues with case 
         for (unsigned int i = 0; i < grainType.length(); i++)
            grainType[i] = tolower(grainType[i]);
         
         // If the grainType is not one of the three Arrayed, throw a bad type exception.
         if (grainType != "wheat" && grainType != "soybean" && grainType != "grain sorghum")
            throw std::string("Bad grain type.");
         
         // Delete everything in tempLine up to and including the first delimiter
         tempLine.erase(0, tempLine.find('|')+1);
         
         /*                Begin Processing Date                   */
         // Copy everything up to the next delimiter, which should contain the date in YYYY-MM-DD
         std::string dateTemp = tempLine.substr(0,tempLine.find('|'));
         
         // Use the removeSpaces function to delete the spaces
         dateTemp = Input::removeSpaces(dateTemp);
         
         // If the string is "AllSpaces", throw an exception
         if (dateTemp == "AllSpaces")
            throw std::string("Date field contains only spaces or is empty.");
         
         // If the length of timeTemp isn't 10 characters, it is not in the correct format
         if (dateTemp.length() != 10)
            throw std::string("Bad date format.");
         
         // Start pulling the individual bits of data from the string
         // YYYY = chars 0-3; MM = chars 5,6; DD = chars 9,10
         std::string yearString, monthString, dayString;
         yearString = dateTemp.substr(0,4);
         monthString = dateTemp.substr(5,2);
         dayString = dateTemp.substr(8,2);
         
         // Check the numbers to be sure they are numbers. If there are any non-number characters, throw an exception
         for (unsigned int i = 0; i < yearString.length(); i++)
            if (!isdigit(yearString[i]))
               throw std::string("Year string " + yearString + " contains non-number characters.");

         for (unsigned int i = 0; i < monthString.length(); i++)
            if (!isdigit(monthString[i]))
               throw std::string("Month string " + monthString + " contains non-number characters.");

         for (unsigned int i = 0; i < dayString.length(); i++)
            if (!isdigit(dayString[i]))
               throw std::string("Day string " + dayString + " contains non-number characters.");

         // Convert them to ints, catching the exceptions as they're thrown
         int year, month, day;
         year = stoi(yearString);
         month = stoi(monthString);
         day = stoi(dayString);
         
         // If the numbers are out of range, throw an exception
         if (month >= 13 || month <= 0 || day >= 32 || day <= 0)
            throw std::string("Date " + yearString + "-" + monthString + "-" + dayString + " out of range.");
         
         // Delete everything in tempLine up to and including the first delimiter
         tempLine.erase(0, tempLine.find('|')+1);         
         
         /*                Begin Processing Time                   */
         // Copy everything up to the next delimiter, which should contain the time in HH:MM:SS
         std::string timeTemp = tempLine.substr(0,tempLine.find('|'));
         
         // Use the removeSpaces function to delete the spaces
         timeTemp = Input::removeSpaces(timeTemp);
         
         // If the string is "AllSpaces", throw an exception
         if (timeTemp == "AllSpaces")
            throw std::string("Time field contains only spaces or is empty.");
         
         // If the length of timeTemp isn't 10 characters, it is not in the correct format
         if (timeTemp.length() != 8)
            throw std::string("Bad time format.");

         // Start pulling the individual bits of data from the string
         // HH = chars 0,1 ; MM = chars 3,4 ; SS = chars 7,8
         std::string hourString, minuteString, secondString;
         hourString = timeTemp.substr(0,2);
         minuteString = timeTemp.substr(3,2);
         secondString = timeTemp.substr(6,2);

         // Check the numbers to be sure they are numbers. If there are any non-number characters, throw an exception
         for (unsigned int i = 0; i < hourString.length(); i++)
            if (!isdigit(hourString[i]))
               throw std::string("Hours string " + hourString + " contains non-number characters.");

         for (unsigned int i = 0; i < minuteString.length(); i++)
            if (!isdigit(minuteString[i]))
               throw std::string("Minutes string " + minuteString + " contains non-number characters.");

         for (unsigned int i = 0; i < secondString.length(); i++)
            if (!isdigit(secondString[i]))
               throw std::string("Seconds string " + secondString + " contains non-number characters.");

         // Convert them to ints, catching the exceptions as they're thrown
         int hour, minute, second;
         hour = stoi(hourString);
         minute = stoi(minuteString);
         second = stoi(secondString);
         
         // If the numbers are out of range, throw an exception
         if (hour >= 24 || hour < 0 || minute >= 60 || minute < 0 || second >= 60 || second < 0 )
            throw std::string("Time " + hourString + ":" + minuteString + ":" + secondString + " out of range.");

         // Delete everything in tempLine up to and including the first delimiter
         tempLine.erase(0, tempLine.find('|')+1);
         
         /*                Begin Processing Ticket name                   */
         // Copy everything up to the next delimiter, which should contain the Gross Weight
         std::string nameString = tempLine.substr(0,tempLine.find('|'));
         
         // Use the removeSpaces function to delete the spaces from nameString
         nameString = Input::removeSpaces(nameString);
         
         // If the string is "AllSpaces", throw an exception
         if (nameString == "AllSpaces")
            throw std::string("Ticket number field contains only spaces or is empty.");
         
         // If the string containing the ticket name isn't alphanumeric, throw an exception
         for (unsigned int i = 0; i < nameString.length(); i++)
            if (!isalnum(nameString[i])) 
               throw std::string("Ticket number string " + nameString + " contains non-Alphanumeric characters.");

         // Delete everything in tempLine up to and including the first delimiter
         tempLine.erase(0, tempLine.find('|')+1);
         
         /*                Begin Processing Gross/Tare Weights                   */
         // Copy everything up to the next delimiter, which should contain the Gross Weight
         std::string grossWeightString = tempLine.substr(0,tempLine.find('|'));
         
         // Delete everything in tempLine up to and including the first delimiter
         tempLine.erase(0, tempLine.find('|')+1);
         
         // We'll go ahead and grab Tare Weight as well, since it'll be useful for an exception
         std::string tareWeightString = tempLine.substr(0,tempLine.find('|'));
         
         // Use the removeSpaces function to delete the spaces from grossWeightString and TareWeightString
         grossWeightString = Input::removeSpaces(grossWeightString);
         tareWeightString = Input::removeSpaces(tareWeightString);
         
         // If the string is "AllSpaces", throw an exception
         if (grossWeightString == "AllSpaces")
            throw std::string("Gross weight field contains only spaces or is empty.");
         
         if (tareWeightString == "AllSpaces")
            throw std::string("Tare weight field contains only spaces or is empty.");

         // Check to be sure the numbers contain no non-digit characters
         for (unsigned int i = 0; i < grossWeightString.length(); i++)
            if (!isdigit(grossWeightString[i]))
               throw std::string("Gross weight string " + grossWeightString + " contains non-number characters.");

         for (unsigned int i = 0; i < tareWeightString.length(); i++)
            if (!isdigit(tareWeightString[i]))
               throw std::string("Tare weight string " + tareWeightString + " contains non-number characters.");

         // Convert them to ints, catching the exceptions as they're thrown
         int grossWeight, tareWeight;
         grossWeight = stoi(grossWeightString);
         tareWeight = stoi(tareWeightString);
         
         // If tareWeight >= grossWeight, throw an exception
         if (tareWeight >= grossWeight)
            throw std::string("Tare weight is greater than gross weight. " + tareWeightString + " >= " + grossWeightString);
         
         // Delete everything in tempLine up to and including the first delimiter
         tempLine.erase(0, tempLine.find('|')+1);
         
         /*          Begin Processing Moisture Level/Foreign Material               */
         // Copy everything up to the next delimiter, which should contain the moisture level
         std::string moistureString = tempLine.substr(0,tempLine.find('|'));
         
         // Delete everything in tempLine up to and including the first delimiter
         tempLine.erase(0, tempLine.find('|')+1);
         
         // We'll finish up the last data value, it should be all that's left in the line
         std::string foreignMatString = tempLine;
         
         // Use the removeSpaces function to delete the spaces from grossWeightString and TareWeightString
         moistureString = Input::removeSpaces(moistureString);
         foreignMatString = Input::removeSpaces(foreignMatString);
         
         // If the string is "AllSpaces", throw an exception
         if (moistureString == "AllSpaces")
            throw std::string("Moisture level field contains only spaces or is empty.");
         
         if (foreignMatString == "AllSpaces")
            throw std::string("Foreign material level field contains only spaces or is empty.");
         
         // Check to make sure they have no non-digit characters except .
         // If the are multiple dots, throw an exception
         int numOfDots = 0;
         for (unsigned int i = 0; i < moistureString.length(); i++){
            if (!isdigit(moistureString[i]) && moistureString[i] != '.')
               throw std::string("Moisture level string " + moistureString + " contains non-number characters.");
            
            if (moistureString[i] == '.')
               numOfDots++;
            
            if (numOfDots > 1)
               throw std::string("Multiple decimal symbols in moisture field " + moistureString + ".");
         }
         
         // Reset numOfDots
         numOfDots = 0;
         for (unsigned int i = 0; i < foreignMatString.length(); i++){
            if (!isdigit(foreignMatString[i]) && foreignMatString[i] != '.')
               throw std::string("Foreign material level string " + foreignMatString + " contains non-number characters.");
            
            if (foreignMatString[i] == '.')
               numOfDots++;
            
            if (numOfDots > 1)
               throw std::string("Multiple decimal symbols in foreign material field " + foreignMatString + ".");
         }
         
         // Convert them to ints, catching the exceptions as they're thrown
         double moistureLevel, foreignMaterials;
         moistureLevel = stod(moistureString);
         foreignMaterials = stod(foreignMatString);
         
         // If moisture level is out of range, throw an exception
         if (moistureLevel >= 100 || moistureLevel < 0)
            throw std::string("Moisture level is out of range.");
         
         // If moisture level is out of range, throw an exception
         if (foreignMaterials >= 100 || foreignMaterials < 0)
            throw std::string("Foreign material level is out of range.");       
         
         // Now, finally, we can create the object
         // Temporary pointer for whatever type we will be making
         Grain* grainTemp;
         
         if (grainType[0] == 'w')
            grainTemp = new Wheat(moistureLevel, foreignMaterials);
         else if (grainType[0] == 's')
            grainTemp = new Soybean(moistureLevel, foreignMaterials);
         else if (grainType[0] == 'g')
            grainTemp = new Milo(moistureLevel, foreignMaterials);
         else
            grainTemp = new Wheat(moistureLevel, foreignMaterials);
         
         // Initialize the time values with a struct tm
         struct tm timeStruct;
         
         timeStruct.tm_sec = second;
         timeStruct.tm_min = minute;
         timeStruct.tm_hour = hour;
         timeStruct.tm_mday = day;
         timeStruct.tm_mon = month - 1;
         timeStruct.tm_year = year - 1900;
         
         // Initialize wday to 0 (not necessary) and isdst to -1 so that it doesn't mess with the hour variable
         timeStruct.tm_wday = 0;
         timeStruct.tm_isdst = -1;
         
         // Create the new Ticket object
         Ticket newTicket(timeStruct, nameString, grossWeight, tareWeight, grainTemp);
         
         // This loop checks for repeat ticket names. If it is a repeat, don't add to the Array
         bool repeatFlag = false;
         
         for (int i = 0; i < (int) tickets.size(); i++) {
            if (newTicket == tickets[i])
               repeatFlag = true;
         }
         
         // If the repeat flag is false, add it to the Array.
         if (repeatFlag == false) {
            tickets.add(newTicket);
         } else {
            std::cout << "Ticket on line " << lineCount << " is a repeat. Ignored." << std::endl;
         }
         
         // Delete the grainTemp object
         delete grainTemp;
      }
      
      // Standard exceptions are caught here
      catch (std::string exceptionString) {
         std::cout << "Standard exception on line " << lineCount << ": " << exceptionString << " Line ignored." << std::endl; 
      }
      
      // Exception provided from getline, if something happens to the file
      catch (const std::ios_base::failure& fail) {
         std::cout << "File error on line " << lineCount << ": " << fail.what() << std::endl;
      }
      
      // Argument provided from stoi, if it just doesn't convert
      catch (const std::invalid_argument& ia) {
         std::cout << "Invalid argument on line " << lineCount << ": " << ia.what() << std::endl;
      }
      
      // Argument provided from stoi, if the number is out of range (it shouldn't be, but still)
      catch (const std::out_of_range& oor) {
         std::cout << "Out of range error on line " << lineCount << ": " << oor.what() << std::endl;
      }
      
      // Argument provided from new, if there is no memory left
      catch (const std::bad_alloc& badAlloc) {
         std::cout << "Memory issue: " << badAlloc.what() << std::endl;
      }
   }
   
   std::cout << "All tickets read." << std::endl << std::endl;
   return true;
}

std::string Input::removeSpaces(std::string inputString)
{
   // Flags for beginning and end character reused from earlier
   bool beginChar = false;
   bool endChar = false;
   
   // Check if the string only contains spaces, or any line termination symbols ('\n' or '\r') or a tab '\t'
   unsigned int spaceCount = 0;
   for (unsigned int i = 0; i < inputString.length(); i++) {
      if (inputString[i] == ' ' || inputString[i] == '\r' || inputString[i] == '\t')
         spaceCount++;
   }
   
   // If spaceCount == length of inputString-1, return a string to be thrown later
   // This also accounts for empty strings
   if (spaceCount == inputString.length())
      return "AllSpaces";
         
   // Start by omitting all beginning spaces, using isnum
   while (!beginChar) {
      if (!isalnum(inputString[0]))
         inputString.erase(0,1);
      else if (isalnum(inputString[0]))
         beginChar = true;
   }
         
   // Then omit all ending spaces
   while (!endChar) {
      if (!isalnum(inputString[inputString.length()-1]))
         inputString.erase((inputString.length()-1), (inputString.length()));
      else if (isalnum(inputString[0]))
         endChar = true;
   }
   
   return inputString;
}
