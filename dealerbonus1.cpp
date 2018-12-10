// Homework 5, Optional Exercise B.1
// dealerbonus1.cpp
// Jackson Steele

#include <iostream>
#include <string>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stddef.h>
#include <GetPot.cpp>
#include <sstream>

using namespace std;

int main(int argc, char ** argv)
 {
   bool verbose = false;
   int percent;
   int concurrent = 1;
   int numtrials;
   int result;

   pid_t pid;
   pid_t terminatedprocess;

   int numsuccesses = 0;
   int numfailures = 0;

   float successes, failures;

   GetPot cmdln(argc, argv);

  opterr = 0;

  if (argc == 1)
    {
      cerr << "Invalid number of parameters entered.\nUsage: dealer -p (0-100) [-v] (number of trials desired)" << endl;
      return 1;
    }

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

  int j = 0;

  for (int i = 0; i < numtrials; i += concurrent)
   {
       for (j = 0; j < concurrent; j++)
        {
	  if ((i + j) < numtrials)
	    if ((pid = fork()) == 0)
	       execvp("./hand", argv);
       	}

       if (pid != 0)
	 {
	   for (j = 0; j < concurrent; j++)
	     {
	       if ((i + j) < numtrials)
		 {
		   terminatedprocess = wait(&result);
		   if (WEXITSTATUS(result) == 1)
		     {
		       numsuccesses++;
		       if (verbose)
			 cout << "PID " << terminatedprocess << " returned Success" << endl;
		     }
		   else
		     {
		       numfailures++;
		       if (verbose)
			 cout << "PID " << terminatedprocess << " returned Failure" << endl;
		     }
		 }
	     }
	 }
   }
   cout << "Created " << numtrials << " processes." << endl;
   successes = numsuccesses*100/numtrials;
   failures = numfailures*100/numtrials;
   cout << "Success - " << (int) successes << "%" << endl;
   cout << "Failure - " << (int) failures << "%" << endl;
}
