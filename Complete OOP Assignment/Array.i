// File name: Array.i
// Author: Alec Trent
// Student ID: U766E384
// Assignment Number: 6

#include <stdexcept>

#include "Array.h"

// 
// ArrayIterator Functions
//

/**
 * Constants
 */
static const int ARRAY_CAPACITY_BLOCK_SIZE = 10;

/**
 * Iterator default constructor
 */
template <class T>
ArrayIterator<T>::ArrayIterator() : container(nullptr), index(-1)
{
}

/**
 * Iterator constructor allowing caller to specify pointer to array and index
 */
template <class T>
ArrayIterator<T>::ArrayIterator(const Array<T> *container, int index) : container(container), index(-1)
{
	if (container) {
		if (index < 0)
			index = 0;
		if (index >= container->arraySize)
			index = -1;
		this->index = index;
	}
}

/**
 * Iterator destructor
 */
template <class T>
ArrayIterator<T>::~ArrayIterator()
{
}

/**
 * Iterator overloaded equality operator ==
 */
template <class T>
bool ArrayIterator<T>::operator ==(const ArrayIterator<T>& iterator) const
{
	int index1 = (container && index == -1) ? container->arraySize : index;
	int index2 = (iterator.container && iterator.index == -1) ? iterator.container->arraySize : iterator.index;

	return (container == iterator.container && index1 == index2);
}

/**
 * Iterator overloaded inequality operator !=
 */
template <class T>
bool ArrayIterator<T>::operator !=(const ArrayIterator<T>& iterator) const
{
	int index1 = (container && index == -1) ? container->arraySize : index;
	int index2 = (iterator.container && iterator.index == -1) ? iterator.container->arraySize : iterator.index;

	return (container != iterator.container || index1 != index2);
}

/**
 * Iterator overloaded relational operator <
 */
template <class T>
bool ArrayIterator<T>::operator <(const ArrayIterator<T>& iterator) const
{
	int index1 = (container && index == -1) ? container->arraySize : index;
	int index2 = (iterator.container && iterator.index == -1) ? iterator.container->arraySize : iterator.index;

	return (container == iterator.container && index1 < index2);
}

/**
 * Iterator overloaded relational operator >
 */
template <class T>
bool ArrayIterator<T>::operator >(const ArrayIterator<T>& iterator) const
{
	int index1 = (container && index == -1) ? container->arraySize : index;
	int index2 = (iterator.container && iterator.index == -1) ? iterator.container->arraySize : iterator.index;

	return (container == iterator.container && index1 > index2);
}

/**
 * Iterator overloaded relational operator <=
 */
template <class T>
bool ArrayIterator<T>::operator <=(const ArrayIterator<T>& iterator) const
{
	int index1 = (container && index == -1) ? container->arraySize : index;
	int index2 = (iterator.container && iterator.index == -1) ? iterator.container->arraySize : iterator.index;

	return (container == iterator.container && index1 <= index2);
}

/**
 * Iterator overloaded relational operator >=
 */
template <class T>
bool ArrayIterator<T>::operator >=(const ArrayIterator<T>& iterator) const
{
	int index1 = (container && index == -1) ? container->arraySize : index;
	int index2 = (iterator.container && iterator.index == -1) ? iterator.container->arraySize : iterator.index;

	return (container == iterator.container && index1 >= index2);
}

/**
 * Iterator overloaded pre-increment operator ++
 */
template <class T>
ArrayIterator<T>& ArrayIterator<T>::operator ++()
{
	// Increment iterator to next item in array (do only if not already at end)
	if (container) {
		int index1 = (index == -1) ? container->arraySize : index;
		index = index1 + 1;
		if (index >= container->arraySize)
			index = -1;
	}
		
	// Return iterator (modified)
	return *this;
}

/**
 * Iterator overloaded post-increment operator ++
 */ 
template <class T>
ArrayIterator<T> ArrayIterator<T>::operator ++(int)
{
	// Create temporary iterator
	ArrayIterator<T> tempIterator = *this;
	
	// Increment iterator to next item in array (do only if not already at end)
	if (container) {
		int index1 = (index == -1) ? container->arraySize : index;
		index = index1 + 1;
		if (index >= container->arraySize)
			index = -1;
	}
	
	// Return temporary iterator (unmodified)
	return tempIterator;
}

/**
 * Iterator overloaded pre-decrement operator --
 */
template <class T>
ArrayIterator<T>& ArrayIterator<T>::operator --()
{
	// Decrement iterator to previous item in array (do only if not already at begin)
	if (container) {
		int index1 = (index == -1) ? container->arraySize : index;
		index = index1 - 1;
		if (index < 0)
			index = 0;
		if (index >= container->arraySize)
			index = -1;
	}
	
	// Return iterator (modified)
	return *this;
}

/**
 * Iterator overloaded post-decrement operator --
 */ 
template <class T>
ArrayIterator<T> ArrayIterator<T>::operator --(int)
{
	// Create temporary iterator
	ArrayIterator<T> tempIterator = *this;
	
	// Decrement iterator to previous item in array (do only if not already at begin)
	if (container) {
		int index1 = (index == -1) ? container->arraySize : index;
		index = index1 - 1;
		if (index < 0)
			index = 0;
		if (index >= container->arraySize)
			index = -1;
	}
	
	// Return temporary iterator (unmodified)
	return tempIterator;
}

/**
 * Iterator overloaded arithmietic addition assignment operator += (index can be pos/neg)
 */ 
template <class T>
ArrayIterator<T>& ArrayIterator<T>::operator +=(int index)
{
	// Increment iterator an indexed number of items in array
	if (container) {
		int index1 = (this->index == -1) ? container->arraySize : this->index;
		this->index = index1 + index;
		if (this->index < 0) 
			this->index = 0;
		if (this->index >= container->arraySize)
			this->index = -1;
	}
	
	// Return iterator (modified)
	return *this;
}

/**
 * Iterator overloaded arithmietic subtraction assignment operator -=
 */ 
template <class T>
ArrayIterator<T>& ArrayIterator<T>::operator -=(int index)
{
	// Decrement iterator an indexed number of items in array
	if (container) {
		int index1 = (this->index == -1) ? container->arraySize : this->index;
		this->index = index1 - index;
		if (this->index < 0) 
			this->index = 0;
		if (this->index >= container->arraySize)
			this->index = -1;
	}
	
	// Return iterator (modified)
	return *this;
}

/**
 * Iterator overloaded arithmietic addition operator +
 */ 
template <class T>
ArrayIterator<T> ArrayIterator<T>::operator +(int index) const
{
	// Create temporary iterator
	ArrayIterator<T> tempIterator = *this;
	
	// Increment iterator an indexed number of items from this iterator in array
	if (tempIterator.container) {
		int index1 = (tempIterator.index == -1) ? tempIterator.container->arraySize : tempIterator.index;
		tempIterator.index = index1 + index;
		if (tempIterator.index < 0) 
			tempIterator.index = 0;
		if (tempIterator.index >= tempIterator.container->arraySize)
			tempIterator.index = -1;
	}
	
	// Return temporary iterator
	return tempIterator;
}

/**
 * Iterator overloaded arithmietic subtraction operator -
 */ 
template <class T>
ArrayIterator<T> ArrayIterator<T>::operator -(int index) const
{
	// Create temporary iterator
	ArrayIterator<T> tempIterator = *this;
	
	// Decrement iterator an indexed number of items from this iterator in array
	if (tempIterator.container) {
		int index1 = (tempIterator.index == -1) ? tempIterator.container->arraySize : tempIterator.index;
		tempIterator.index = index1 - index;
		if (tempIterator.index < 0) 
			tempIterator.index = 0;
		if (tempIterator.index >= tempIterator.container->arraySize)
			tempIterator.index = -1;
	}
	
	// Return temporary iterator
	return tempIterator;
}

/**
 * Iterator overloaded arithmietic subtraction operator -
 */ 
template <class T>
int ArrayIterator<T>::operator -(const ArrayIterator<T>& iterator) const throw (std::invalid_argument)
{
	// Determine indexed number of items in array between this iterator and iterator provided 
	if (container && iterator.container) {
		int index1 = (index == -1) ? container->arraySize : index;
		int index2 = (iterator.index == -1) ? iterator.container->arraySize : iterator.index;
		return (index1 - index2);
	}

	throw std::invalid_argument("Uninitialized iterator");
}

/**
 * Iterator overloaded dereference operator *
 */
template <class T>
T& ArrayIterator<T>::operator *() const throw (std::out_of_range)
{
	if (container) {
		int index1 = (index == -1) ? container->arraySize : index;
		if (index1 < container->arraySize)
			return container->array[index1];
	}
	
	throw std::out_of_range("Trying to derefernce outside of array boundaries");
}

/**
 * Iterator overloaded member pointer operator ->
 */
template <class T>
T* ArrayIterator<T>::operator ->() const throw (std::out_of_range)
{
	if (container) {
		int index1 = (index == -1) ? container->arraySize : index;
		if (index1 < container->arraySize)
			return &container->array[index1];
	}
	
	throw std::out_of_range("Trying to dereference outside of array boundaries");
}

/**
 * Iterator overloaded array operator []
 */
template <class T>
T& ArrayIterator<T>::operator [](int index) const throw (std::out_of_range)
{
	if (container) {
		int index1 = (this->index == -1) ? container->arraySize : this->index;
		if (index1 + index < container->arraySize)
			return container->array[index1 + index];
	}
	
	throw std::out_of_range("Trying to dereference outside of array boundaries");
}

/**
 * Iterator non-member overloaded arithmietic addition operator +
 */ 
template <class T2>
ArrayIterator<T2> operator +(int index, const ArrayIterator<T2>& iterator)
{
	// Create temporary iterator
	ArrayIterator<T2> tempIterator = iterator;
	
	// Increment iterator an indexed number of items from this iterator in array
	if (tempIterator.container) {
		int index1 = (tempIterator.index == -1) ? tempIterator.container->arraySize : tempIterator.index;
		tempIterator.index = index1 + index;
		if (tempIterator.index < 0) 
			tempIterator.index = 0;
		if (tempIterator.index >= tempIterator.container->arraySize)
			tempIterator.index = -1;
	}
	
	// Return temporary iterator
	return tempIterator;
}

/**
 * Iterator non-member overloaded arithmietic subtraction operator -
 */ 
template <class T2>
ArrayIterator<T2> operator -(int index, const ArrayIterator<T2>& iterator)
{
	// Create temporary iterator
	ArrayIterator<T2> tempIterator = iterator;
	
	// Decrement iterator an indexed number of items from this iterator in array
	if (tempIterator.container) {
		int index1 = (tempIterator.index == -1) ? tempIterator.container->arraySize : tempIterator.index;
		tempIterator.index = index1 - index;
		if (tempIterator.index < 0) 
			tempIterator.index = 0;
		if (tempIterator.index >= tempIterator.container->arraySize)
			tempIterator.index = -1;
	}
	
	// Return temporary iterator
	return tempIterator;
}

//
// Array class functions
//

// Default constructor
template <class T>
Array<T>::Array()
{
   array = NULL;
   arrayCapacity = 0;
   arraySize = 0;
}

// Copy constructor
template <class T>
Array<T>::Array(const Array<T>& items)
{
   // Set the values for array capacity and size equal
   arrayCapacity = items.arrayCapacity;
   arraySize = items.arraySize;
      
   // Allocate a new array of same capacity as the one we're gonna copy
   array = new T[arrayCapacity];   
   
   // For loop to copy the array
   for (int i = 0; i < (int) arraySize; i++)
      array[i] = items.array[i];
}

// Destructor, deallocates the array
template <class T>
Array<T>::~Array()
{
   delete[] array;
}

// Returns an iterator pointing to the beginning of the array
// Uses ArrayIterator's overloaded constructor and this as the pointer to the container
template <class T>
ArrayIterator<T> Array<T>::begin()
{
   return ArrayIterator<T>(this, 0);
}

// Returns an iterator pointing to the end of the array
// ArraySize is used since it points to the logical end of the array
template <class T>
ArrayIterator<T> Array<T>::end()
{
   return ArrayIterator<T>(this, arraySize);
}

template <class T>
void Array<T>::add(const T& item)
{  
   // If the array is full, allocate ten more spots to a temp array, copy the data between arrays, and add the new item
   // Otherwise, simply add the item
   if (arrayCapacity == arraySize){
      // First declare a array2 to hold the data we're gonna copy
      T* array2;
      
      // Allocate ten more spots than is currently available to array
      // Also, increment arrayCapacity by 10
      array2 = new T[arrayCapacity+10];
      arrayCapacity += 10;
      
      // For loop to copy the array
      for (int i = 0; i < (int) arraySize; i++)
         array2[i] = array[i];
         
      // Add the new item to the end of the current data
      array2[arraySize] = item;
      
      // Set the old array equal to array2 and delete array (original)
      delete[] array;
      array = array2;
   } else {
      array[arraySize] = item;
   }
   
   // Increment the values of arraySize
   arraySize++;
}

// Returns the number of items in the array
template <class T>
unsigned int Array<T>::size() const
{
   return arraySize;
}

// Overloaded assignment operator =
template <class T>
const Array<T>& Array<T>::operator =(const Array<T>& items)
{
   // Check if items == items, return items if true
   if (this == &items) {
      return *this;
   } else {
      // Set the values for array capacity and size equal
      arrayCapacity = items.arrayCapacity;
      arraySize = items.arraySize;
      
      // If the item array contains items, delete them. Otherwise, continue
      if (array != NULL)
         delete[] array;
      
      // Re-initialize array to a new array of same capacity as the calling object
      array = new T[arrayCapacity];
      
      // For loop to copy the array
      for (int i = 0; i < (int) arraySize; i++)
         array[i] = items.array[i];
      
      // Return the items object
      return *this;
   }
}


// Overloaded array operator []
template <class T>
T& Array<T>::operator [](int index) const
{
   return array[index];
} 
