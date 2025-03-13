
#ifndef _LABELED_GPS_H_
#define _LABELED_GPS_H_

// Labeled_GPS.h

// Instructional Plan --
// Inheritance ==> Is-A relationship among classes

// GPS: the parent class
// Labeled_GPS: the derived/child class
// a Labeled_GPS object "is a" GPS object.
// features: constructor, casting (moving up and down in the inheritance hierarchy) 

// today -- single inheritance, constructors, casting, virtual functions, operator-overloading
	     // why do we need casting?
	     // moving up and down from IH

// Comparison ==>
// C++:    Single, Multiple, Virtual
// Java:   Single (but it has the Interface feature to handle MI)
// Python: Single, Multiple (but it is equivalent to Virtual Inheritance in C++)

// uncertainty in object-oriented programming
// such that we HAVE TO "guess and verify", even for experienced programmers --

// (1) operator overloading
// Are you sure about the semantics of the operators?

// (2) inheritance (signle, multiple, virtual)
// Is this member function defined in the current class or by one of the ancesters?

// (3) polymorphism (virtual functions in C++)
// Do you even know what is the "current" class?

// AFTER all the above, we will talke about

	     // Multiple Inheritance
	     // Virtual Inheritance
	     // Object Memory Layout
	     // JSONRPC and Proxy Objects


// Questions from the 10/23/2023 lecture
// (1) How to define a Single Inheritance relationship? [public, protected, private, virtual]
// (2) How to move "up and down" from a Single Inheritance Hierarchy?
// ==> cast up via reference (casting is done by the compiler, NOT run-time !!!)
// ==> cast down via reference if it is Single Inheritance
// ==> you cannot cast down at all if it is Virtual Inheritance

// (3) How are objects, including those inherited components, allocated in memory?
// (4) What is a virtual function?
	     // virtual table pointer
	     // TWO conditions to apply the concept of virtual functions to our program --
	     // (1) we need to up-cast a whole bunch of objects to their base or ancester.
	     // convert all the Labeled_GPS objects to GPS_DD objects
	     // convert all the Google_Map_GPS objects also to GPS_DD objects
	     // --> all objects are not GPS_DD objects

// (4.5) Or, what is the difference between the object creation time and the object access time?
// The above questions are pretty much all we need to worry for midterm #3.

#include "GPS.h"

// class Labeled_GPS : virtual public GPS_DD

class Labeled_GPS : public GPS_DD
{
 private:
 protected:
 public:
  std::string label;

  Labeled_GPS();
  Labeled_GPS(double, double, std::string);

  bool operator==(Labeled_GPS&);

  virtual bool setGPSLabel(std::string);
  virtual Json::Value * dump2JSON(void);
  virtual void JSON2Object(Json::Value *);
};

#endif /* _LABELED_GPS_H_ */
