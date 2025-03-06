
#ifndef _JVTIME_H_
#define _JVTIME_H_

#include "ee1520_Common.h"
#include "ee1520_Exception.h"

using namespace std;

class JvTime
{
 private:
 protected:
 public:
  bool good;
  int year;
  int month;
  int day;
  int hour;
  int minute;
  int second;
  char tail4[64];

  JvTime(const char *);
  JvTime() { }
  int Parse(const char *);
  struct std::tm * getStdTM(void);
  int setStdTM(struct std::tm *);
  std::string * getTimeString(void);

  bool operator==(JvTime& arg_jvt);
  bool operator< (JvTime& arg_jvt);
  double operator-(JvTime& arg_jvt);
  
  virtual Json::Value * dump2JSON(void);
  virtual void JSON2Object(Json::Value *);
};

JvTime *getNowJvTime(void);

#endif /* _JVTIME_H_ */
