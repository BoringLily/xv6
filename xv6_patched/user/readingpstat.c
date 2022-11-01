#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstat.h"

int
main(int argc, char *argv[])
{
  int i;
  struct pstat LaTable;
  getpinfo(&LaTable);
  for(i=0 ; i<25 ; i++)
  {
    printf(1, MAGENTA"USE: %d "CYAN" TICKETS: %d"WHITE" TICKS: %d "CYAN" STIRDE: %d "MAGENTA"PASSVALUE: %d\n"RESET, LaTable.inuse[i], LaTable.tickets[i],LaTable.ticks[i],LaTable.stride[i], LaTable.passvalue[i]);
  }
  exit();
}
