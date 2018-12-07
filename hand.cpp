#include <iostream>
#include <string>
#include <unistd.h>
#include <stdlib.h>
#include <rng/gsl_rng.h>

using namespace std;

gsl_rng * myrng;

int main(int argc, char ** argv)
 {
   int percent;
   int numtrials;
   bool verbose;
   int result;

   const gsl_rng_type * rngtype;

   int c;

  opterr = 0;

  while ((c = getopt(argc, argv, "p:v")) != -1)
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
