
// ee1520_JSON.cpp
// #define _EE1520_DEBUG_

#include "ee1520_Common.h"
#include "JvTime.h"

// pre-check will check null pointer, JSON object format

void
JSON2Object_precheck
(Json::Value * arg_json_ptr, ee1520_Exception * arg_exception_ptr,
 int arg_where_code)
{
  Exception_Info * ei_ptr = NULL;

  if (arg_json_ptr == ((Json::Value *) NULL))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = arg_where_code;
      ei_ptr->which_string = "default";
      ei_ptr->how_code = EE1520_ERROR_NORMAL;
      ei_ptr->what_code = EE1520_ERROR_NULL_JSON_PTR;
      ei_ptr->array_index = 0;
      (arg_exception_ptr->info_vector).push_back(ei_ptr);
      throw (*arg_exception_ptr);
    }
  
  if ((arg_json_ptr->isNull() == true) ||
      (arg_json_ptr->isObject() != true))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = arg_where_code;
      ei_ptr->which_string = "default";
      ei_ptr->how_code = EE1520_ERROR_NORMAL;

      if (arg_json_ptr->isNull() == true)
	{
	  ei_ptr->what_code = EE1520_ERROR_JSON_KEY_MISSING;
	}
      else
	{
	  ei_ptr->what_code = EE1520_ERROR_JSON_KEY_TYPE_MISMATCHED;
	}
      
      ei_ptr->array_index = 0;

      (arg_exception_ptr->info_vector).push_back(ei_ptr);
      throw (*arg_exception_ptr);
    }
  
  return;
}

void
JSON2Object_appendEI
(ee1520_Exception& arg_e, ee1520_Exception *arg_exception_ptr,
 unsigned int arg_index)
{
  // this should not happen...
  if (arg_exception_ptr == NULL) return;
  
  int ei;
  for (ei = 0; ei < (arg_e.info_vector).size(); ei++)
    {
      Exception_Info * ei_ptr_copy = new Exception_Info {};
      ((Exception_Info&) (*ei_ptr_copy)) = ((Exception_Info&) (*((arg_e.info_vector)[ei])));
      ei_ptr_copy->array_index = arg_index;
      (arg_exception_ptr->info_vector).push_back(ei_ptr_copy);
    }
  arg_e.myDestructor();
  return;
}

void
myPrintLog
(std::string content, std::string fname)
{
  if (fname.size() == 0) return;
  
  FILE *log_f = fopen(fname.c_str(), "a");
  if (log_f == NULL) return;
  
  JvTime *jv_ptr = getNowJvTime();
  std::string *str_ptr = jv_ptr->getTimeString();
  fprintf(log_f, "[%s] %s\n", str_ptr->c_str(), content.c_str());

  delete str_ptr;
  delete jv_ptr;
  
  fflush(log_f);
  fclose(log_f);
  return;
}

int
myParseJSON
(std::string input, Json::Value * jv_ptr)
{
  if (jv_ptr == NULL) return EE1520_ERROR_NULL_JSON_PTR;

  Json::CharReaderBuilder builder;
  Json::CharReader* reader;
  std::string errors;
  bool parsingSuccessful;

  reader = builder.newCharReader();
  parsingSuccessful = reader->parse(input.c_str(),
				    input.c_str() + input.size(),
				    jv_ptr, &errors);
  delete reader;

  if (!parsingSuccessful) {
    std::cout << "Failed to parse the content of the first JSON, errors:" << std::endl;
    std::cout << errors << std::endl;
    return EE1520_ERROR_JSON_PARSING;
  }
  
  return EE1520_ERROR_NORMAL;
}

char *
myFile2String
(char *f_name)
{
  if (f_name == NULL) return NULL;
  FILE * f_ptr = fopen(f_name, "r");
  if (f_ptr == NULL) return NULL;

  long lSize;
  size_t lresult;

  fseek(f_ptr, 0 , SEEK_END);
  lSize = ftell(f_ptr);
  rewind(f_ptr);

  // allocate memory to contain the whole file:
  char *result_ptr = (char *) malloc(sizeof(char)*(lSize+1));
  // copy the file into the buffer:
  lresult = fread(result_ptr, 1, lSize, f_ptr);
  fclose(f_ptr);

  if (lresult != lSize)
    {
      fputs("Reading error", stderr);
      free(result_ptr);
      return NULL;
    }

  return result_ptr;
}

int
myFile2JSON
(char *f_name, Json::Value * jv_ptr)
{
  int rc;

  char *json_str = myFile2String(f_name);
  std::cout << f_name             << std::endl;
  // std::cout << ((void*) json_str) << std::endl;
  // std::cout << (jv_ptr)           << std::endl;

  if (json_str == NULL)
    {
      rc = EE1520_ERROR_FILE_NOT_EXIST;
    }
  else
    {
      rc = myParseJSON(json_str, jv_ptr);
      free(json_str);
    }
  return rc;
}

int
myJSON2File
(char *f_name, Json::Value * jv_ptr)
{
  if (f_name == NULL) return -1;
  if (jv_ptr == NULL) return -2;

  FILE * f_ptr = fopen(f_name, "w");
  if (f_ptr == NULL)
    {
      std::cout << f_name << " fopen for write failed myJSON2File" << std::endl;
      return EE1520_ERROR_FILE_NOT_EXIST;
    }

  std::string json_str = (*jv_ptr).toStyledString();
  int msize = json_str.size() + 1;
  char *json_buf_ptr = (char *) malloc(msize);
  bzero(json_buf_ptr, msize);
  snprintf(json_buf_ptr, msize, "%s", json_str.c_str());

  long lSize;
  size_t lresult;

  lSize = strlen(json_buf_ptr);
  std::cout << f_name << " " << lSize <<  std::endl;
  lresult = fwrite(json_buf_ptr, 1, lSize, f_ptr);
  free(json_buf_ptr);
  fclose(f_ptr);

  if (lresult != lSize)
    {
      fputs("Writing error", stderr);
      return EE1520_ERROR_FILE_WRITE;
    }

  return EE1520_ERROR_NORMAL;
}

const char *ee1520error[] =
  {
    "Normal",
    "Incorrect vsID in history",
    "Incorrect vsID in Post ID",
    "JSON_Post_Merging failed",
    "lresult lSize mismatch",
    "JSON Parsing Error",
    "JSON_2_Post failed",
    "JSON Post No ID",
    "JSON Value pointer NULL",
    "File not Exist",
    "File Read Error",
    "File Name Pointer Null",
    "File Write Error",
    "Less Than 5 History Records",
    "No Search Keyword Found",
    "No OKey Found",
    "No OKey Found and very Strange",
    "Time Interval too Short for this Post",
    "Search Keyword Format Incorrect",
    "std set struct tm Error",
    "Null C++ Object Pointer",
    "Post ID Mismatched",
    "Please experiment this JSON with Server 2, port 55408 instead",
    "JSON2Object class Action",
    "JSON2Object class Comment",
    "JSON2Object class Commutable",
    "JSON2Object class Core",
    "JSON2Object class GPS_DD",
    "JSON2Object class Holdable",
    "JSON2Object class JvTime",
    "JSON2Object class Labeled_GPS",
    "JSON2Object class Link",
    "JSON2Object class Locatable",
    "JSON2Object class Message",
    "JSON2Object class OKey",
    "JSON2Object class Person",
    "JSON2Object class Post",
    "JSON2Object class Reaction",
    "JSON2Object class Record",
    "JSON2Object class Tag",
    "JSON2Object class Team",
    "JSON2Object class Thing",
    "JSON Value Key missing",
    "JSON Value Key Value Type mismatched",
    "JvTime String format",
    "Post ID Check Failed",
    "JSONRPC Server",
    "JSONRPC Client",
    "Strlen >= 1023",
    "ID being set Twice",
    "JSON2Object class Timed_Location",
    "JSON2Object class Personal_Timed_GPS_Record",
    "Invalid Error Code (EE1520_ERROR_MAX)",
  };

const char *
error_string
(int code)
{
  if ((code > 0) || (code <= EE1520_ERROR_MAX))
    {
      return ee1520error[(-1) * EE1520_ERROR_MAX];
    }
  else
    {
      return ee1520error[(-1) * code];
    }
}

int
produceErrorJSON
(ee1520_Exception e, const char log_file_name[], Json::Value *jv_ptr, int extra)
{
  printf("Producing errors\n");
  if (((e.info_vector).size() <= 0) ||
      (jv_ptr == NULL) ||
      (log_file_name == NULL))
    return EE1520_ERROR_NULL_JSON_PTR;

  printf("Producing errors Check 2\n");

  jv_ptr = e.dump2JSON();
  myPrintLog((*jv_ptr).toStyledString(), log_file_name);
  printf("Produced errors\n");
  return EE1520_ERROR_NORMAL;
}

bool
check_JSON_Keys
(vector<std::string> arg_keys, Json::Value arg_json)
{
  int ik;

  for (ik = 0; ik < arg_keys.size(); ik++)
    {
      if (arg_json[arg_keys[ik]].isNull() == true)
	return false;
    }
  return true;
}

const vector<std::string>
keys_Thing =
  {
    "description",
    "model",
    "sequence num",
    "url",
  };
  
const vector<std::string>
keys_Locatable =
  {
    "description",
    "location",
    "model",
    "sequence num",
    "url",
  };

const vector<std::string>
keys_Holdable =
  {
    "description",
    "holder",
    "location",
    "model",
    "sequence num",
    "url",
  };

const vector<std::string>
keys_Person =
  {
    "home",
    "name",
    "vsID",
  };

const vector<std::string>
keys_Team =
  {
    "members",
    "name",
  };

JSON_Diff::~JSON_Diff
(void)
{
  if (this->updated != NULL) delete this->updated;
}

Json::Value *
JSON_Diff::dump2JSON
(void)
{
  Json::Value * result_ptr = new Json::Value ();

  (*result_ptr)["order"] = ((unsigned int) this->order);
  (*result_ptr)["diff"]  = this->diff;
  (*result_ptr)["type"]  = this->type;

  if (this->updated != NULL)
    {
      (*result_ptr)["updated"]  = (this->updated)->dump2JSON();
    }
  
  int i;
  Json::Value jv_array;
  for (i = 0; i < (this->key_path).size(); i++)
    {
      jv_array[i] = (this->key_path)[i];
    }
  (*result_ptr)["key path"]["data"]  = jv_array;
  (*result_ptr)["key path"]["count"] = ((unsigned int) (this->key_path).size());
  
  return result_ptr;
}

vector<JSON_Diff *> *
JSON_Difference
(Json::Value arg_first, Json::Value arg_second, vector<std::string> arg_prefix)
{
  int i;
  vector<JSON_Diff *> * result_ptr = new vector<JSON_Diff *> ();

  if ((arg_first.isNull()   == true ) ||
      (arg_second.isNull()  == true ))
    {
      return result_ptr;
    }
  
  if ((arg_first.isObject()  == false) ||
      (arg_second.isObject() == false))
    {
      if (arg_first == arg_second) return result_ptr;
      
      // the values are different.
      JSON_Diff * lv_JD_ptr_1 = new JSON_Diff ();
      for (i = 0; i < arg_prefix.size(); i++)
	{
	  (lv_JD_ptr_1->key_path).push_back(arg_prefix[i]);
	}

      lv_JD_ptr_1->type = "Value";
      lv_JD_ptr_1->order = 1;
      lv_JD_ptr_1->diff = arg_first;
      result_ptr->push_back(lv_JD_ptr_1);

      JSON_Diff * lv_JD_ptr_2 = new JSON_Diff ();
      for (i = 0; i < arg_prefix.size(); i++)
	{
	  (lv_JD_ptr_2->key_path).push_back(arg_prefix[i]);
	}

      lv_JD_ptr_2->type = "Value";
      lv_JD_ptr_2->order = 2;
      lv_JD_ptr_2->diff = arg_second;
      result_ptr->push_back(lv_JD_ptr_2);
      return result_ptr;
    }
  
  vector<std::string> lv_first_members;
  std::cout << arg_first << std::endl;
  lv_first_members = arg_first.getMemberNames();

  vector<std::string> lv_second_members;
  std::cout << arg_second << std::endl;
  lv_second_members = arg_second.getMemberNames();
  
  int k1, k2;
  k1 = 0;
  k2 = 0;

  while((k1 < lv_first_members.size()) &&
	(k2 < lv_second_members.size()))
    {
      if (lv_first_members[k1] == lv_second_members[k2])
	{
  	  vector<JSON_Diff *> * sub_ptr = NULL;

	  vector<std::string> prefix_copy = arg_prefix;
	  prefix_copy.push_back(lv_first_members[k1]);
	  sub_ptr = JSON_Difference(arg_first[lv_first_members[k1]],
				    arg_second[lv_second_members[k2]],
				    prefix_copy);

	  for (i = 0; i < sub_ptr->size(); i++)
	    {
	      result_ptr->push_back((*sub_ptr)[i]);
	    }
	  delete sub_ptr;
	  
	  k1++;
	  k2++;
	}
      else
	{
	  JSON_Diff * lv_JD_ptr = new JSON_Diff ();
	  lv_JD_ptr->type = "Key";

	  for (i = 0; i < arg_prefix.size(); i++)
	    {
	      (lv_JD_ptr->key_path).push_back(arg_prefix[i]);
	    }
	  
	  if (lv_first_members[k1] > lv_second_members[k2])
	    {
	      // this means that k-first is "moving" down the "list" faster.
	      // this also means that k-second has something missed by k-first.
	      (lv_JD_ptr->key_path).push_back(lv_second_members[k2]);
	      lv_JD_ptr->order = 2;
	      lv_JD_ptr->diff = arg_second[lv_second_members[k2]];
	      k2++;
	    }
	  else
	    {
	      // otherwise...
	      (lv_JD_ptr->key_path).push_back(lv_first_members[k1]);
	      lv_JD_ptr->order = 1;
	      lv_JD_ptr->diff = arg_first[lv_first_members[k1]];
	      k1++;
	    }
	  result_ptr->push_back(lv_JD_ptr);
	}
    }

  while (k1 < lv_first_members.size())
    {
      JSON_Diff * lv_JD_ptr = new JSON_Diff ();
      lv_JD_ptr->type = "Key";
      
      for (i = 0; i < arg_prefix.size(); i++)
	{
	  (lv_JD_ptr->key_path).push_back(arg_prefix[i]);
	}

      (lv_JD_ptr->key_path).push_back(lv_first_members[k1]);
      lv_JD_ptr->order = 1;
      lv_JD_ptr->diff = arg_first[lv_first_members[k1]];
      k1++;
      result_ptr->push_back(lv_JD_ptr);
    }
  
  while (k2 < lv_second_members.size())
    {
      JSON_Diff * lv_JD_ptr = new JSON_Diff ();
      lv_JD_ptr->type = "Key";
      
      for (i = 0; i < arg_prefix.size(); i++)
	{
	  (lv_JD_ptr->key_path).push_back(arg_prefix[i]);
	}

      (lv_JD_ptr->key_path).push_back(lv_second_members[k2]);
      lv_JD_ptr->order = 2;
      lv_JD_ptr->diff = arg_first[lv_second_members[k2]];
      k2++;
      result_ptr->push_back(lv_JD_ptr);
    }
  
  return result_ptr;
}

std::string
Identifier::get
(void)
{
  std::string result = "";
  
  if (this->profile == "")
    {
      return result;
    }
  result += (this->profile);

  if (this->post == "")
    {
      return result;
    }
  result += ("_" + this->post);

  if (this->comment == "")
    {
      return result;
    }
  result += ("_" + this->comment);

  return result;
}

int
Identifier::setPP
(std::string arg_id_string)
{
  int rc = EE1520_ERROR_NORMAL;
  std::string profile_id;
  std::string post_id;

  char idstr[1024];
  bzero(idstr, 1024);

  // check if the id string is too big!
  unsigned int idstr_length = strlen(arg_id_string.c_str());

  if (idstr_length >= 1023)
    {
      rc = EE1520_ERROR_STRLEN_GE_1023;
      idstr_length = 1023;
    }
  snprintf(idstr, idstr_length + 1, "%s", arg_id_string.c_str());

  if (idstr[0] != '\0')
    {
      char c_prof_buf[1024];
      char c_post_buf[1024];
      bzero(c_prof_buf, 1024);
      bzero(c_post_buf, 1024);

      sscanf(idstr, "%[^_]_%s", c_prof_buf, c_post_buf);
      profile_id = c_prof_buf;
      post_id    = c_post_buf;
    }
  else
    {
      rc = EE1520_ERROR_JSON_POST_NO_ID;
    }

  if (rc == EE1520_ERROR_NORMAL)
    {
      // Profile and Post ID can be only set once!!
      if ((this->profile == "") &&
	  (this->post    == ""))
	{
  	  this->profile = profile_id;
	  this->post    = post_id;
	}

      if ((this->profile != profile_id) ||
	  (this->post    != post_id))
	{
	  rc = EE1520_ERROR_ID_SET_TWICE;
	}
    }

  return rc;
}

int
Identifier::setPPC
(std::string arg_id_string)
{
  int rc = EE1520_ERROR_NORMAL;

  char c_prof_buf[1024];
  char c_post_buf[1024];
  char c_comm_buf[1024];
  char c_PP_buf[1024];

  bzero(c_prof_buf, 1024);
  bzero(c_post_buf, 1024);
  bzero(c_comm_buf, 1024);
  bzero(c_PP_buf, 1024);

  sscanf(arg_id_string.c_str(), "%[^_]_%[^_]_%s", c_prof_buf, c_post_buf, c_comm_buf);
  snprintf(c_PP_buf, strlen(c_prof_buf) + strlen("_") + strlen(c_post_buf) + 1,
	   "%s_%s", c_prof_buf, c_post_buf);

  rc = this->setPP(c_PP_buf);
  
  if (rc == EE1520_ERROR_NORMAL)
    {
      std::string comment_id = { c_comm_buf };
      this->comment = comment_id;
    }
  
  return rc;
}

bool
Identifier::operator==
(Identifier& aIdentifier)
{
  if ((this->comment == "") && (aIdentifier.comment == ""))
    {
      // this is probably unnecessary, but I am having a strange bug... :-(
      return ((this->profile == aIdentifier.profile) &&
	      (this->post    == aIdentifier.post));
    }
  else
    {
      return ((this->profile == aIdentifier.profile) &&
	      (this->post    == aIdentifier.post)    &&
	      (this->comment == aIdentifier.comment));
    }
}

vector<std::string>
matchDirent
(std::string dir_str, std::string prefix, std::string profile_id)
{
  vector<std::string> result;
  DIR * dirp = opendir(dir_str.c_str());
  if (dirp != NULL)
    {
      struct dirent * dp;
      while ((dp = readdir(dirp)) != NULL)
	{
	  if (strlen(dp->d_name) < 1023)
	    {
	      char buff[1024];
	      bzero(buff, 1024);
	      snprintf(buff, strlen(dp->d_name) + 1, "%s", dp->d_name);
	      char *name_ptr = buff;
	      if (strncmp(name_ptr, prefix.c_str(), strlen(prefix.c_str())) == 0)
		{
		  name_ptr += (strlen(prefix.c_str()) + 1);
		  if (strncmp(name_ptr, profile_id.c_str(), strlen(profile_id.c_str())) == 0)
		    {
		      result.push_back(dp->d_name);
		    }
		}
	    }
	}
      closedir(dirp);
    }
  return result;
}
