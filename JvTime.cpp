
#include "JvTime.h"
#include "string.h"

JvTime *
getNowJvTime
(void)
{
  time_t ticks; 
  ticks = time(NULL);
  struct std::tm * my_tm_ptr = gmtime(&ticks);
  JvTime * jvT_ptr = new JvTime();
  int rc = jvT_ptr->setStdTM(my_tm_ptr);
  if (rc != 0)
    {
      std::cout << "error: failed to set time!" << std::endl;
      delete jvT_ptr;
      return NULL;
    }
  return jvT_ptr;
}

int
JvTime::Parse
(const char *time_str)
{
  const char zero_str[] = "0000-00-00T00:00:00+0000";    

  if ((time_str == NULL) || (strlen(time_str) != strlen(zero_str)))
    {
      return EE1520_ERROR_NULL_CPP_PTR;
    }

  if (((time_str[0] < '0') || (time_str[0] > '9')) ||
      ((time_str[1] < '0') || (time_str[1] > '9')) ||
      ((time_str[2] < '0') || (time_str[2] > '9')) ||
      ((time_str[3] < '0') || (time_str[3] > '9')) ||
      (time_str[4] != '-') ||
      ((time_str[5] < '0') || (time_str[5] > '9')) ||
      ((time_str[6] < '0') || (time_str[6] > '9')) ||
      (time_str[7] != '-') ||
      ((time_str[8] < '0') || (time_str[8] > '9')) ||
      ((time_str[9] < '0') || (time_str[9] > '9')) ||
      (time_str[10] != 'T') ||
      ((time_str[11] < '0') || (time_str[11] > '9')) ||
      ((time_str[12] < '0') || (time_str[12] > '9')) ||
      (time_str[13] != ':') ||
      ((time_str[14] < '0') || (time_str[14] > '9')) ||
      ((time_str[15] < '0') || (time_str[15] > '9')) ||
      (time_str[16] != ':') ||
      ((time_str[17] < '0') || (time_str[17] > '9')) ||
      ((time_str[18] < '0') || (time_str[18] > '9')) ||
      (time_str[19] != '+') ||
      ((time_str[20] < '0') || (time_str[20] > '9')) ||
      ((time_str[21] < '0') || (time_str[21] > '9')) ||
      ((time_str[22] < '0') || (time_str[22] > '9')) ||
      ((time_str[23] < '0') || (time_str[23] > '9')))
    {
      return EE1520_ERROR_TIME_STRING_FORMAT;
    }

  sscanf(time_str, "%4d-%2d-%2dT%2d:%2d:%2d+%4s",
	 &(this->year), &(this->month), &(this->day),
	 &(this->hour), &(this->minute), &(this->second),
	 this->tail4);

  // std::cout << *(this->getTimeString()) << std::endl;
  
  return EE1520_ERROR_NORMAL;
}

JvTime::JvTime
(const char *time_str)
{
  const char zero_str[] = "0000-00-00T00:00:00+0000";    
  if (this->Parse(time_str) != EE1520_ERROR_NORMAL)
    {
      sscanf(zero_str, "%4d-%2d-%2dT%2d:%2d:%2d+%4s",
	     &(this->year), &(this->month), &(this->day),
	     &(this->hour), &(this->minute), &(this->second),
	     this->tail4);
    }
  return;
}

struct std::tm *
JvTime::getStdTM
(void)
{
  struct std::tm * result = (struct std::tm *) malloc(sizeof(struct std::tm));
  bzero(result, sizeof(struct std::tm));

  result->tm_sec = this->second;
  result->tm_min = this->minute;
  result->tm_hour = this->hour;
  result->tm_mday = this->day;
  result->tm_mon = (this->month) - 1;
  result->tm_year = (this->year) - 1900;

  return result;
}

int
JvTime::setStdTM
(struct std::tm *arg_tm_ptr)
{
  if (arg_tm_ptr == NULL) return -1;

  this->second = arg_tm_ptr->tm_sec;
  this->minute = arg_tm_ptr->tm_min;
  this->hour   = arg_tm_ptr->tm_hour;
  this->day    = arg_tm_ptr->tm_mday;
  this->month  = (arg_tm_ptr->tm_mon) + 1;
  this->year   = (arg_tm_ptr->tm_year) + 1900;

  bzero(this->tail4, 16);
  snprintf(this->tail4, strlen("0000") + 1, "0000");

  return 0;
}

std::string *
JvTime::getTimeString
(void)
{
  struct std::tm * tm_ptr = this->getStdTM();

  char buffer[128];
  bzero(buffer, 128);
  std::strftime(buffer, 32, "%Y-%m-%dT%H:%M:%S+", tm_ptr);
  snprintf(buffer, strlen(buffer) + strlen(this->tail4) + 1,
	   "%s%s", buffer, this->tail4);
  return (new std::string(buffer));
}

bool
JvTime::operator==
(JvTime& arg_jvt)
{
  return ((this->year == arg_jvt.year) && 
	  (this->month == arg_jvt.month) && 
	  (this->day == arg_jvt.day) && 
	  (this->hour == arg_jvt.hour) && 
	  (this->minute == arg_jvt.minute) && 
	  (this->second == arg_jvt.second));
}

bool
JvTime::operator<
(JvTime& arg_jvt)
{
  if (this->year <= arg_jvt.year)
    {
      if (this->year < arg_jvt.year)
	{
	  return true;
	}
      else
	{
	  if(this->month <= arg_jvt.month)
	    {
	      if (this->month < arg_jvt.month)
		{
		  return true;
		}
	      else
		{
		  if (this->day <= arg_jvt.day)
		    {
		      if (this->day < arg_jvt.day)
			{
			  return true;
			}
		      else
			{
			  if (this->hour <= arg_jvt.hour)
			    {
			      if (this->hour < arg_jvt.hour)
				{
				  return true;
				}
			      else
				{
				  if (this->minute <= arg_jvt.minute)
				    {
				      if (this->minute < arg_jvt.minute)
					{
					  return true;
					}
				      else
					{
					  if (this->second <= arg_jvt.second)
					    {
					      if (this->second < arg_jvt.second)
						{
						  return true;
						}
					      else
						{
						  return false;
						}
					    }
					}
				    }
				}
			    }
			}
		    }
		}
	    }
	}
    }

  return false;
}

double
JvTime::operator-
(JvTime& arg_jvt)
{
  // arg_jvt should be older timestamp
  
  struct tm *end_tm_ptr = this->getStdTM();
  if (end_tm_ptr == NULL) return 0.0;
  struct tm *begin_tm_ptr = arg_jvt.getStdTM();
  if (begin_tm_ptr == NULL) return 0.0;

  // end, beginning
  double result_diff = difftime(mktime(end_tm_ptr), mktime(begin_tm_ptr)); 
  free(end_tm_ptr);
  free(begin_tm_ptr);
  
  return result_diff;
}

Json::Value *
JvTime::dump2JSON
(void)
{
  Json::Value * result_ptr = new Json::Value();
  (*result_ptr)["time"] = (*(this->getTimeString()));
  return result_ptr;
}

void
JvTime::JSON2Object
(Json::Value * arg_json_ptr)
{
  Exception_Info * ei_ptr = NULL;
  ee1520_Exception lv_exception {};
  ee1520_Exception * lv_exception_ptr = &lv_exception;

  JSON2Object_precheck(arg_json_ptr, lv_exception_ptr,
		       EE1520_ERROR_JSON2OBJECT_JVTIME);

  if (((*arg_json_ptr)["time"].isNull() == true) ||
      ((*arg_json_ptr)["time"].isString() == false))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = EE1520_ERROR_JSON2OBJECT_JVTIME;
      ei_ptr->which_string = "time";
      ei_ptr->how_code = EE1520_ERROR_NORMAL;

      if ((*arg_json_ptr)["time"].isNull() == true)
	{
	  ei_ptr->what_code = EE1520_ERROR_JSON_KEY_MISSING;
	}
      else
	{
	  ei_ptr->what_code = EE1520_ERROR_JSON_KEY_TYPE_MISMATCHED;
	}
      (lv_exception_ptr->info_vector).push_back(ei_ptr);
    }
  else
    {
      int rc = this->Parse((((*arg_json_ptr)["time"]).asString()).c_str());
      if (rc != EE1520_ERROR_NORMAL)
	{
	  ei_ptr = new Exception_Info {};
	  ei_ptr->where_code = EE1520_ERROR_JSON2OBJECT_JVTIME;
	  ei_ptr->which_string = "time";
	  ei_ptr->how_code = EE1520_ERROR_NORMAL;
	  ei_ptr->what_code = rc;
	  (lv_exception_ptr->info_vector).push_back(ei_ptr);
	}
    }

  if ((lv_exception_ptr->info_vector).size() != 0)
    {
      throw (*lv_exception_ptr);
    }

  return;
}
