#ifndef _PSTAT_H_
#define _PSTAT_H_

#include "param.h"

struct pstat {
  int inuse[NPROC];
  int tickets[NPROC];
  int pid[NPROC];
  int ticks[NPROC];
  int passvalue[NPROC]; //current pass value (ticks*10)*stride
  int stride[NPROC];
};
#endif // _PSTAT_H_