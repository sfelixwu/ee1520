//

#ifndef _EE1520_EXCEPTION_
#define _EE1520_EXCEPTION_

#include "ee1520_Common.h"

class Exception_Info
{
private:
protected:
public:
  int where_code;
  int what_code;
  std::string which_string;
  int how_code;
  unsigned int array_index;

  Exception_Info() { array_index = 0; }
  Exception_Info& operator=(Exception_Info& aExceptionInfo)
  {
    this->where_code   = aExceptionInfo.where_code;    // location, which class
    this->what_code    = aExceptionInfo.what_code;     // error content
    this->which_string = aExceptionInfo.which_string;  // which attribute
    this->how_code     = aExceptionInfo.how_code;      // which function pointer (future)
    this->array_index  = aExceptionInfo.array_index;
    // std::cout << "copy Exception_Info\n";
    return (*this);
  }
};

class ee1520_Exception : public std::exception
{
private:
protected:
public:
  std::vector<Exception_Info *> info_vector; // we could consider map or Json::Value
  
  void myDestructor(void);
  ~ee1520_Exception() throw () {}
  virtual const char* what() const throw () { return "ee1520 exception"; }
  virtual Json::Value * dump2JSON(void);  
};

int produceErrorJSON(ee1520_Exception, const char [], Json::Value *, int);
void JSON2Object_precheck(Json::Value *, ee1520_Exception *, int);
void JSON2Object_appendEI(ee1520_Exception&, ee1520_Exception *, unsigned int);

#endif /* _EE1520_EXCEPTION_ */
