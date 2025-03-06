
#include "ee1520_Common.h"

using namespace std;

int
main
(int argc, char *argv[])
{
  if (argc != 2)
    {
      char arg_string[] = " <parsing_json>";
      std::cout << "usage: " << argv[0] << arg_string << std::endl; 
      return -1;
    }

  // getting the JSON to be parsed
  Json::Value jv;
  int rc = myFile2JSON(argv[1], &jv);
  fprintf(stdout, "rc = %d\n", rc);

  return 0;
}
