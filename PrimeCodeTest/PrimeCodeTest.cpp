#include <cmath> // sqrt
#include <ctime> // clock()
#include <iostream>

using namespace std;

void bluntPrimeTest (int upperBound) 
{
   // Set a timestamp equal to the current time
   // We use clock() from ctime for ms resolution
   int clockBefore = clock();
   
   // For loop to iterate through however many numbers we want, determined by upperBound
   // We start with two because one is weird as far as primality goes.
   for (int i = 2; i <= upperBound; i++)
   {
      // Boolean flag to determine if i is prime or not
      bool isNotPrime = false;
      
      // Serial division for testing the prime, from one to the number
      for (int j = 2; j < i; j++)
      {
         // If J cleanly divides I, break
         if (i % j == 0)
            isNotPrime = true;
      }
      
      if (!isNotPrime)
         cout << i << " is a prime." << endl;
   }
   
   // Output the time in milliseconds that it took to complete
   cout << "Operation took " << (clock() - clockBefore) << " ms to complete." << endl;
}

void sqrtOptimizedPrimeTest (int upperBound)
{
   // Set a timestamp equal to the current time
   // We use clock() from ctime for ms resolution
   int clockBefore = clock();
   
   // Again, a for loop to iterate through all numbers from 1 to upperBound
   // We start with two because one is weird as far as primality goes.
   for (int i = 2; i <= upperBound; i++)
   {
      // Boolean flag to determine if i is prime or not
      bool isNotPrime = false;
      
      // We take the square root of the number and divide up to and including that, since anything beyond is unnecessary
      for (int j = 2; j <= sqrt(i); j++)
      {
         // If J cleanly divides I, break
         if (i % j == 0)
            isNotPrime = true;
      }

      if (!isNotPrime)
         cout << i << " is a prime." << endl;
   }
   
   // Output the time in milliseconds that it took to complete
   cout << "Operation took " << (clock() - clockBefore) << " ms to complete." << endl;
}

void primeGenerationTest (int upperBound)
{
   // Set a timestamp equal to the current time
   // We use clock() from ctime for ms resolution
   int clockBefore = clock();
   
   /* A special property of primes is used here, that almost all primes are of form (6k +/- 1)
   / We will operate on a basis of generating numbers using this
   / Since it does not cleanly iterate, we will use a while loop
   / Starting with 1 excludes primes 2, 3; however, this generation algorithm does not work for those low primes anyways */
   int i = 1;
   while ((6 * i - 1) <= upperBound)
   {
      int lowerTest = (6 * i - 1);
      int upperTest = (6 * i + 1);
      int sqrtLower = sqrt(lowerTest);
      int sqrtUpper = sqrt(upperTest);
      
      // Boolean flag to determine if i is prime or not
      bool isNotPrime = false;
            
      // Test primality on the number of form 6k-1
      for (int j = 2; j <= sqrtLower; j++)
      {
         if (lowerTest % j == 0)
            isNotPrime = true;
      }

      if (!isNotPrime)
         cout << sqrtLower << " is a prime. k = " << i <<endl;
      
      // Resetting isNotPrime
      isNotPrime = false;
      
      // Test primality on the number of form 6k+1
      for (int j = 2; j <= sqrtUpper; j++)
      {
         if (upperTest % j == 0)
            isNotPrime = true;  
      }
      
      if (!isNotPrime)
         cout << sqrtUpper << " is a prime. k = " << i << endl;
         
      // Iterate I
      i++;
   }

   // Output the time in milliseconds that it took to complete
   cout << "Operation took " << (clock() - clockBefore) << " ms to complete." << endl;
}

// Overloaded main function with arguments
int main (int argc, char* argv[])
{
   // If there are no arguments given, run the functions to 50. Otherwise, execute based on the arguments provided.
   if (argc == 1){
      bluntPrimeTest(50);
      cout << "----------------------------------------------------------------" << endl;
      sqrtOptimizedPrimeTest(50);
      cout << "----------------------------------------------------------------" << endl;
      primeGenerationTest(50);
      cout << "----------------------------------------------------------------" << endl;
   } else {
      // Block that chooses which algorithm to use
      // Set the argument in argv[1], which should be the algorithm type, to lowercase
      string algorithmChoice = argv[1];
      for (unsigned int i = 0; i < algorithmChoice.length(); i++)
            algorithmChoice[i] = tolower(algorithmChoice[i]);
            
      if (argc != 3) {
         cout << "Improper number of arguments provided. Exiting." << endl;
      } else if (atoi(argv[2]) <= 1 || isnan(atoi(argv[2]))) {
         cout << "Improper third argument \"" << argv[2] << "\" given. Exiting." << endl; 
      } else {
         if (algorithmChoice == "blunt"){
            bluntPrimeTest(atoi(argv[2]));
         } else if (algorithmChoice == "sqrt"){
            sqrtOptimizedPrimeTest(atoi(argv[2]));      
         } else if (algorithmChoice == "generation"){
            primeGenerationTest(atoi(argv[2]));
         } else if (algorithmChoice == "all"){
            bluntPrimeTest(atoi(argv[2]));
            cout << "----------------------------------------------------------------" << endl;
            sqrtOptimizedPrimeTest(atoi(argv[2]));
            cout << "----------------------------------------------------------------" << endl;
            primeGenerationTest(atoi(argv[2]));
            cout << "----------------------------------------------------------------" << endl;
         } else {
            cout << "Invalid algorithm choice \"" << argv[1] << "\" provided." << endl << "Please select one of the following: " << endl 
            << "\"blunt\" for serial division up to the number" << endl
            << "\"sqrt\" for the square root optimized algorithm (serial division up to square root of number)" << endl
            << "\"generation\" to use the 6k+1 method of generating primes, then testing them using sqrt." << endl
            << "\"All\" to run all tests with the number provided." << endl;
         }
      }
   }
   
   // Allows us to read the output
   cout << "Please press enter to exit.";
   string exit;
   getline(cin, exit);
   
   return 0;
}
