#include <iostream>
#include <string>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main(int argc, char ** argv)
 {
   bool verbose = false;
   int percent;
   int concurrent = 1;
   int numtrials;
   int result;

   //  char* newcmdln[6];

   pid_t pid;
   pid_t terminatedprocess;

   int numsuccesses = 0;
   int numfailures = 0;

   float successes, failures;

   //  int index;
   int c;

  opterr = 0;

  if (argc == 1)
    {
      cerr << "Invalid number of parameters entered.\nUsage: dealer -p (0-100) [-v] (number of trials desired)" << endl;
      return 1;
    }

  while ((c = getopt(argc, argv, "p:t:v")) != -1)
    switch (c)
      {
      case 'p':
        percent = atoi(optarg);
	if (percent > 100 || percent < 0)
	  {
	    cerr << "Invalid percentage entered (valid: 0-100)." << endl;
	    return 1;
	  }
	else if (percent == 0 && optarg[0] != '0')
	  {
	    cerr << "Non-digit entered for percentage (valid: 0-100)." << endl;
	    return 1;
	  }
        break;
      case 't':
	concurrent = atoi(optarg);
	if (concurrent > 8 || concurrent < 1)
	  {
	    cerr << "This program supports a maximum of 8 and a minimum of 1 concurrent processes. Terminating" << endl;
	    return 1;
	  }
	break;
      case 'v':
        verbose = true;
        break;
      case '?':
        if (optopt == 'p')
          cerr << "Option " << char(optopt) << " requires an argument." << endl;
        else
          cerr << "Unknown option " << char(optopt) << endl;
	return 1;
      default:
        abort ();
      }

  if (optind < argc)
      numtrials = atoi(argv[optind]);
  else
    {
      cerr << "The last parameter should be the number of desired iterations." << endl;
      return 1;
    }

  //  cout << "Concurrent = " << concurrent << endl;

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
