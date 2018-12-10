// Homework 5, Optional Exercise B.1
// handbonus1.cpp
// Jackson Steele

#include <iostream>
#include <string>
#include <unistd.h>
#include <stdlib.h>
#include <rng/gsl_rng.h>
#include <stddef.h>
#include <GetPot.cpp>

using namespace std;

gsl_rng * myrng;

int main(int argc, char ** argv)
 {
   int percent;
   int numtrials;
   bool verbose;
   int concurrent;
   int result;

   const gsl_rng_type * rngtype;

   GetPot cmdln(argc, argv);

  opterr = 0;

  if (argc == 1)
    {
      cerr << "Invalid number of parameters entered.\nUsage: dealer -p (0-100) [-v] (number of trials desired)" << endl;
      return 1;
    }

if (cmdln.search("-f"))
    {
      string tempstring;
      tempstring = cmdln.next("");
      if (tempstring == "")
	{
	  cerr << "Error: File name not given after -f option." << endl;
	  return 1;
	}
      else
	{
	  GetPot fileparser(tempstring);
	   if (fileparser.search("-v"))
	     verbose = true;

	   if (fileparser.search("-p"))
	     {
	       percent = fileparser.next(-1);
	       if (percent > 100 || percent < 0)
		 {
		   cerr << "Invalid percentage entered (valid: 0-100)." << endl;
		   exit(1);
		 }
	     }
	   else
	     {
	       cerr << "You failed to enter a percent value.\nUsage: dealer -p (0-100) [-v] (number of trials desired)" << endl;
	       return 1;
	     }

	   if (fileparser.search("-t"))
	     {
	       concurrent = fileparser.next(-1);
	       if (concurrent < 1 || concurrent > 8)
		 {
		   cerr << "Invalid number of concurrent processes entered. Minimum of 1 and maximum of 8 supported." << endl;
		   exit(1);
		 }
	     }
	   else
	     concurrent = 1;

	    if (fileparser.search("-n"))
	     {
	       numtrials = fileparser.next(-1);
	       if (numtrials <= 0)
		 {
		   cerr << "Invalid number of trial entered. (valid > 0)." << endl;
		   exit(1);
		 }
	     }
	   else
	     {
	       cerr << "You failed to enter the number of trials desired." << endl;
	       return 1;
	     }
	}
    }

  else
    {
      if (cmdln.search("-v"))
	verbose = true;

      if (cmdln.search("-p"))
	{
	  percent = cmdln.next(-1);
	  if (percent > 100 || percent < 0)
	    {
	      cerr << "Invalid percentage entered (valid: 0-100)." << endl;
	      exit(1);
	    }
	}
      else
	{
	  cerr << "You failed to enter a percent value.\nUsage: dealer -p (0-100) [-v] (number of trials desired)" << endl;
	  return 1;
	}

      if (cmdln.search("-t"))
	{
	  concurrent = cmdln.next(-1);
	  if (concurrent < 1 || concurrent > 8)
	    {
	      cerr << "Invalid number of concurrent processes entered. Minimum of 1 and maximum of 8 supported." << endl;
	      exit(1);
	    }
	}
      else
	concurrent = 1;

      stringstream tempstring(cmdln[argc-1]);

      tempstring >> numtrials;

      if (numtrials <= 0)
	{
	  cerr << "Invalid number of trials entered. (valid > 0)." << endl;
	  exit(1);
	}
    }

   gsl_rng_env_setup();

   rngtype = gsl_rng_default;
   myrng = gsl_rng_alloc (rngtype);

   gsl_rng_set(myrng, (getpid() * 1000)); // seeding with PID*1000 for better accuracy
  
   result = gsl_rng_uniform_int (myrng, 100);

   gsl_rng_free (myrng);

   if (result < percent)
     return 1;
   else
     return 0;
}
