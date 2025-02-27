
// testing for C programming language by S. Felix Wu
// for Cyber Security MS applicant, 10/24/2024

#include <stdio.h>
#include <stdlib.h>

struct some_struct
{
  unsigned int ss_attr_01;
  double       ss_attr_02;
  char         ss_attr_03[1024];
  void        *ss_attr_04;
  int          ss_attr_05;
};

int
main(void)
{
  fprintf(stdout, "%lld\n", ((long long) (&((struct some_struct *) 0)->ss_attr_01)));
  fprintf(stdout, "%lld\n", ((long long) (&((struct some_struct *) 0)->ss_attr_02)));
  fprintf(stdout, "%lld\n", ((long long) (&((struct some_struct *) 0)->ss_attr_03)));
  fprintf(stdout, "%lld\n", ((long long) (&((struct some_struct *) 0)->ss_attr_04)));
  fprintf(stdout, "%lld\n", ((long long) (&((struct some_struct *) 0)->ss_attr_05)));
  return 0;
}

// The following questions were designed for experienced C programmers (though many professional
// cannot answer the question correctly). We do NOT expect you to know the complete answer.
// Therefore, please provide the best guess!!

// Question 1: will the above program cause any compiler-time or run-time error(s)?
//   Question 1.1: what is the difference between compiler-time and run-time errors?
// Question 2.a: if with errors, what kind of errors should we expect?
// Question 2.b: if no error, what is the purpose of the above program?
//             (Please describe the best you can, but briefly)
// Question 3: if no error, what should be the output (hint: an integer) of this program?
//             (assuming the program is being executed on a 64-bits computer architecture.)

