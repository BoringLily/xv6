#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstat.h"

int
main(int argc, char *argv[])
{
  int rc, i;
  double p = 0;

  for(i=1 ; i<=5 ; i++)
  {
    rc = fork();
    if(rc < 0)
    {
      printf(1, "Fork Failure Detected at %d\n", i);
      return -1;
    }
    else if(rc == 0)
    {
      settickets(i*10);
      for(;;)
      {
      p++;
      }
      exit();
    }
  }
  printf(1,GREEN "\nDONE\n"RESET);
  exit();
}
