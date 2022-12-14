#include "types.h"
#include "x86.h"
#include "defs.h"
#include "param.h"
#include "mmu.h"
#include "proc.h"
#include "sysfunc.h"
#include "pstat.h"


int counterPartA = 0;

int counterPartB = 0;

int sysCallTracker[25];

int sys_settickets(void)
{
  int num;
  if(argint(0, &num) < 0)
  {
    return -1;
  }
  else
  {
    return settickets(num);
  }
}

int
sys_getpinfo(void)
{
  struct pstat *pTable;
	if(argptr(0, (void *)&pTable, sizeof(*pTable)) < 0)
  {
		return -1;
	}
	if(pTable == NULL)
  { 
		return -1;
	}			
	getpinfo(pTable);	
	return 0;
}

int sys_sct(void)
{
  int n;

  if (argint(0, &n) < 0)
    return -1;

  return sysCallTracker[n];
}

int sys_fork(void)
{

  return fork();
}

int sys_exit(void)
{
 
  exit();
  return 0; // not reached
}

int sys_wait(void)
{
  
  return wait();
}

int sys_kill(void)
{
  
  int pid;

  if (argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int sys_getpid(void)
{
  
  counterPartA++;
  return proc->pid;
}

int sys_FirstPart(void)
{
  
  return counterPartA;
}

int sys_SecondPart(void)
{
  return counterPartB;
}

int sys_sbrk(void)
{
  
  int addr;
  int n;

  if (argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
  if (growproc(n) < 0)
    return -1;
  return addr;
}

int sys_sleep(void)
{
  
  int n;
  uint ticks0;

  if (argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while (ticks - ticks0 < n)
  {
    if (proc->killed)
    {
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since boot.
int sys_uptime(void)
{
  
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
