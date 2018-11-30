// File name: Array.h
// Author: Alec Trent
// Student ID: U766E384
// Assignment Number: 7

#ifndef ARRAY_H_
#define ARRAY_H_

/**
 * This Array class is templated to hold any type, but here it will hold a Ticket
 **/
 
namespace ContainerTemplate
{
   /**
    * Provide forward references to classes
    */
   template <class T>
   class Array;
   
   /**
    * The ArrayIterator template class identifies properties of a list iterator of type T
    **/
   template <class T>
   class ArrayIterator : public std::iterator<std::random_access_iterator_tag, T> {
     public:
   	// Default constructor
   	ArrayIterator();
   
   	// Destructor
   	~ArrayIterator();
   
   	// Overloaded equality operator ==
   	bool operator ==(const ArrayIterator<T>& iterator) const;
   
   	// Overloaded inequality operator !=
   	bool operator !=(const ArrayIterator<T>& iterator) const;
   
   	// Overloaded relational operator <
   	bool operator <(const ArrayIterator<T>& iterator) const;
   
   	// Overloaded relational operator >
   	bool operator >(const ArrayIterator<T>& iterator) const;
   
   	// Overloaded relational operator <=
   	bool operator <=(const ArrayIterator<T>& iterator) const;
   
   	// Overloaded relational operator >=
   	bool operator >=(const ArrayIterator<T>& iterator) const;
   
   	// Overloaded pre-increment operator ++
   	ArrayIterator<T>& operator ++();
   
   	// Overloaded post-increment operator ++
   	ArrayIterator<T> operator ++(int);
   
   	// Overloaded pre-decrement operator --
   	ArrayIterator<T>& operator --();
   
   	// Overloaded post-decrement operator --
   	ArrayIterator<T> operator --(int);
   
   	// Overloaded arithmetic addition assignment operator += (index can be pos/neg)
   	ArrayIterator<T>& operator +=(int index);
   
   	// Overloaded arithmetic subtraction assignment operator -= (index can be pos/neg)
   	ArrayIterator<T>& operator -=(int index);
   
   	// Overloaded arithmetic addition operator + (index can be pos/neg)
   	ArrayIterator<T> operator +(int index) const;
   
   	// Overloaded arithmetic subtraction operator - (index can be pos/neg)
   	ArrayIterator<T> operator -(int index) const;
   
   	// Overloaded arithmetic subtraction operator -
   	int operator -(const ArrayIterator<T>& iterator) const throw (std::invalid_argument);
   
   	// Overloaded dereference operator *
   	T& operator *() const throw (std::out_of_range);
   
   	// Overloaded member pointer operator ->
   	T* operator ->() const throw (std::out_of_range);
   
   	// Overloaded array operator []
   	T& operator [](int index) const throw (std::out_of_range);
   
   	// Friend classes
   	friend class Array<T>;
   
   	// Friend non-member overloaded arithmetic addition operator +
   	template <class T2>
   	friend ArrayIterator<T2> operator +(int index, const ArrayIterator<T2>& iterator);
   
   	// Friend non-member overloaded arithmetic subtraction operator -
   	template <class T2>
   	friend ArrayIterator<T2> operator -(int index, const ArrayIterator<T2>& iterator);
   
     private:
   	// Constructor allowing caller to specify pointer to array and index to current item
   	ArrayIterator(const Array<T> *container, int index);
   
   	// Member variables
   	const Array<T> *container;	// Pointer to container
   	int index;					// index to item in container's array (forced to -1 for end)
   };
   
   template <class T>
   class Array {
     public:
 		// Friend classes
	   friend class ArrayIterator<T>;  
     
   	// Constructor default
   	Array();
   
   	// Copy constructor
   	Array(const Array<T>& items);
   
   	// Destructor
   	~Array();
   	
   	// Returns an iterator at the beginning of the array
   	ArrayIterator<T> begin();
   	
   	// Returns an iterator at the logical end of the array (last element index + 1)
   	ArrayIterator<T> end();
   
   	// Add a ticket to the dynamic array
   	void add(const T& item);
   
   	// Return size of array of items (number of tickets in array)
   	unsigned int size() const;
   
   	// Overloaded assignment operator =
   	const Array<T>& operator =(const Array<T>& items);
   
   	// Overloaded array operator []
   	T& operator [](int index) const;
   
     private:
   	// Member variables
   	T *array;				// Pointer to array of items
   	int arrayCapacity;	// Number of items the array currently has space for
   	int arraySize;		// Number of items added to the array
   };
   
   #include "Array.i"
}

#endif /* TICKETS_H_ */
