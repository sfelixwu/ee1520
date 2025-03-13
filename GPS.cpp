
#include "GPS.h"

GPS_DD::GPS_DD()
{
  this->class_name = "GPS_DD";
  this->latitude = 0.0;
  this->longitude = 0.0;
}

GPS_DD::GPS_DD(double arg_latitude, double arg_longitude)
{
  this->class_name = "GPS_DD";
  this->latitude = arg_latitude;
  this->longitude = arg_longitude;
}

const double 
GPS_DD::getLatitude()
{
  return this->latitude;
}
 
const double
GPS_DD::getLongitude
()
{
  return this->longitude;
}

// DD distance calculation

/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
/*::                                                                         :*/
/*::  This routine calculates the distance between two points (given the     :*/
/*::  latitude/longitude of those points). It is being used to calculate     :*/
/*::  the distance between two locations using GeoDataSource(TM) products.   :*/
/*::                                                                         :*/
/*::  Definitions:                                                           :*/
/*::    South latitudes are negative, east longitudes are positive           :*/
/*::                                                                         :*/
/*::  Passed to function:                                                    :*/
/*::    lat1, lon1 = Latitude and Longitude of point 1 (in decimal degrees)  :*/
/*::    lat2, lon2 = Latitude and Longitude of point 2 (in decimal degrees)  :*/
/*::    unit = the unit you desire for results                               :*/
/*::           where: 'M' is statute miles (default)                         :*/
/*::                  'K' is kilometers                                      :*/
/*::                  'N' is nautical miles                                  :*/
/*::  Worldwide cities and other features databases with latitude longitude  :*/
/*::  are available at https://www.geodatasource.com                         :*/
/*::                                                                         :*/
/*::  For enquiries, please contact sales@geodatasource.com                  :*/
/*::                                                                         :*/
/*::  Official Web site: https://www.geodatasource.com                       :*/
/*::                                                                         :*/
/*::           GeoDataSource.com (C) All Rights Reserved 2018                :*/
/*::                                                                         :*/
/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

#include <math.h>
#define pi 3.14159265358979323846

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
/*::  Function prototypes                                           :*/
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
double deg2rad(double);
double rad2deg(double);

double GeoDataSource_distance(double lat1, double lon1, double lat2, double lon2, char unit) 
{
  double theta, dist;
  if ((lat1 == lat2) && (lon1 == lon2))
    {
      return 0;
    }
  else
    {
      theta = lon1 - lon2;
      dist = sin(deg2rad(lat1)) * sin(deg2rad(lat2)) + cos(deg2rad(lat1)) * cos(deg2rad(lat2)) * cos(deg2rad(theta));
      dist = acos(dist);
      dist = rad2deg(dist);
      dist = dist * 60 * 1.1515;
      switch(unit)
	{
	case 'M':
	  break;
	case 'K':
	  dist = dist * 1.609344;
	  break;
	case 'N':
	  dist = dist * 0.8684;
	  break;
	}
      return (dist);
    }
}

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
/*::  This function converts decimal degrees to radians             :*/
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
double deg2rad(double deg)
{
  return (deg * pi / 180);
}

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
/*::  This function converts radians to decimal degrees             :*/
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
double rad2deg(double rad)
{
  return (rad * 180 / pi);
}

double
GPS_DD::distance
(GPS_DD another)
{
  return GeoDataSource_distance(this->latitude, this->longitude,
				another.getLatitude(), another.getLongitude(), 'M');
}

bool
GPS_DD::operator==
(GPS_DD& another)
{
  return((this->latitude  == another.getLatitude())   &&
	 (this->longitude == another.getLongitude()));
}

bool
GPS_DD::operator<
(GPS_DD& another)
{
  if (this->latitude < another.getLatitude()) return true;

  if ((this->latitude == another.getLatitude()) &&
      (this->longitude < another.getLongitude()))
      return true;

  return false;
}

Json::Value *
GPS_DD::dump2JSON
(void)
{
  // printf("GPS_DD dump2JSON start\n");
  Json::Value * result_ptr = new Json::Value();

  (*result_ptr)["latitude"]  = this->latitude;
  (*result_ptr)["longitude"] = this->longitude;

  return result_ptr;
}

void
GPS_DD::JSON2Object
(Json::Value * arg_json_ptr)
{
  Exception_Info * ei_ptr = NULL;
  ee1520_Exception lv_exception {};
  ee1520_Exception * lv_exception_ptr = &lv_exception;

  JSON2Object_precheck(arg_json_ptr, lv_exception_ptr,
		       EE1520_ERROR_JSON2OBJECT_GPS_DD);
  
  if ((((*arg_json_ptr)["latitude"]).isNull() == true) ||
      (((*arg_json_ptr)["latitude"]).isDouble() != true))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = EE1520_ERROR_JSON2OBJECT_GPS_DD;
      ei_ptr->which_string = "latitude";
      ei_ptr->how_code = EE1520_ERROR_NORMAL;

      if ((*arg_json_ptr)["latitude"].isNull() == true)
	{
	  ei_ptr->what_code = EE1520_ERROR_JSON_KEY_MISSING;
	}
      else
	{
	  ei_ptr->what_code = EE1520_ERROR_JSON_KEY_TYPE_MISMATCHED;
	}

      ei_ptr->array_index = 0;

      (lv_exception_ptr->info_vector).push_back(ei_ptr);
    }
  else
    {
      this->latitude = ((*arg_json_ptr)["latitude"]).asDouble();
      if (((this->latitude) > 90.0) || ((this->latitude) < -90.0))
	{
	  this->latitude = 0.0; 
	}
    }

  if ((((*arg_json_ptr)["longitude"]).isNull() == true) ||
      (((*arg_json_ptr)["longitude"]).isDouble() != true))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = EE1520_ERROR_JSON2OBJECT_GPS_DD;
      ei_ptr->which_string = "longitude";
      ei_ptr->how_code = EE1520_ERROR_NORMAL;

      if ((*arg_json_ptr)["longitude"].isNull() == true)
	{
	  ei_ptr->what_code = EE1520_ERROR_JSON_KEY_MISSING;
	}
      else
	{
	  ei_ptr->what_code = EE1520_ERROR_JSON_KEY_TYPE_MISMATCHED;
	}

      ei_ptr->array_index = 0;

      (lv_exception_ptr->info_vector).push_back(ei_ptr);
    }
  else
    {
      this->longitude = ((*arg_json_ptr)["longitude"]).asDouble();
      if (((this->longitude) > 180.0) || ((this->longitude) < -180.0))
	{
	  this->longitude = 0.0; 
	}
    }

  if ((lv_exception_ptr->info_vector).size() != 0)
    {
      throw (*lv_exception_ptr);
    }

  return;
}
