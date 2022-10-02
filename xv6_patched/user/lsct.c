/*
  @file lsct.c
  @brief List System Call Table
*/

#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

#define TotalSysCalls 25
#define nameWidth 22
#define maxSpacing 9

char* callName[] =
{
  "",
  "SYS_fork      ",
  "SYS_exit      ",   
  "SYS_wait      ",
  "SYS_pipe      ",  
  "SYS_write     ",
  "SYS_read      ",
  "SYS_close     ",
  "SYS_kill      ",
  "SYS_exec      ",
  "SYS_open      ",
  "SYS_mknod     ",
  "SYS_unlink    ",
  "SYS_fstat     ",
  "SYS_link      ",
  "SYS_mkdir     ",
  "SYS_chdir     ",
  "SYS_dup       ",
  "SYS_getpid    ",
  "SYS_sbrk      ",
  "SYS_sleep     ",
  "SYS_uptime    ",
  "SYS_FirstPart ",
  "SYS_SecondPart",
  "SYS_sct       "
};

int digitLength(int x) {
    if (x >= 1000000000) return 10;
    if (x >= 100000000)  return 9;
    if (x >= 10000000)   return 8;
    if (x >= 1000000)    return 7;
    if (x >= 100000)     return 6;
    if (x >= 10000)      return 5;
    if (x >= 1000)       return 4;
    if (x >= 100)        return 3;
    if (x >= 10)         return 2;
    return 1;
}
void printSpace(int n)
{
  for(int j = 0; j<n; j++)
    {
      printf(1," ");
    }
}


void pHeader(int n)
{
printf(1, "  ");

for(int i = 0; i<(n+nameWidth) ;i++)
{
  printf(1, "#");
}

printf(1, "\n");
}



int
main(int argc, char *argv[])
{
  // ARG parameters
  uint ignoreSCT = 0; // ignore the SYS_sct calls made during this program
  uint padRows = 0; // add lines after each row
  uint nonZero = 0; // print only nonzero counts if true

  printf(1, RESET "  Use arg \'help\' for the help menu\n\n" RESET);

  if(argc == 2)
  {
    char *arg = argv[1];
    if(arg[0]=='h')
    {
      printf(1, "Arguments: \n");
      printf(1, "\t" BLUE "-n" RESET"  <-- prints all non-zero values\n" RESET);
      printf(1, "\t" BLUE "-i" RESET"  <-- ignore the SYS_sct calls made during this program\n" RESET);
      printf(1, "\t" BLUE "-p" RESET"  <-- add lines after each row\n" RESET);
      printf(1, "Example:\n\t" RESET"To use multiple arguments enter them together such as "BLUE" -ni \n\n" RESET);
      exit();
    }
    for(int i = 1; i< strlen(arg); i++)
    {
      switch(arg[i])
      {
      case 'n':
        nonZero = 1;
        break;
      case 'i':
        ignoreSCT = 1;
        break;
      case 'p':
        padRows = 1;
      default:
        break;
      }
    }
  }

  int total = 0;
  int callList[TotalSysCalls];

  int i;

  int digitSpacing[25];
  char padding[10];
  char dash[] = "--------------";

  for(i = 1; i < TotalSysCalls; i++)
  {
    callList[i] = sct(i);
    digitSpacing[i] = digitLength(callList[i])-1;
  }
  
  if(ignoreSCT)
  {
    callList[24] -= 24;
  }

  for(i = 0; i<=maxSpacing; i++)
  {
    padding[i] = '-';
  }
  

  printf(1, GREEN"  System Call Table\n\n"RESET);
  
  printf(1,"  +----+-%s-+-%s-+\n", dash, padding);
  printf(1,"  | "YELLOW"ID"RESET" | "MAGENTA"Sys Call Names"RESET" | "BLUE"Call Count"RESET" |\n");
  printf(1,"  +----+-%s-+-%s-+\n", dash, padding);
  
  
  // Draw table
  for(i = 1; i < TotalSysCalls; i++)
  {
    if(!nonZero || callList[i]!=0)
    {
      total = total + callList[i];

      printf(1,"  | "YELLOW"%s%d"RESET" | "MAGENTA"%s"RESET" |", i>=10 ? "":" ", i , callName[i]);

      printSpace(maxSpacing-digitSpacing[i]);

      printf(1," "BLUE"%d"RESET" |\n", callList[i]);

      if(padRows)
      {
        printf(1,"  +----+-%s-+-%s-+\n", dash, padding);
      }
    }
  }

  if(!padRows)
  {
    printf(1,"  +----+-%s-+-%s-+\n", dash, padding);
  }
  

  printf(1,"\n  Total system Calls: %d \n\n", total);
  

  exit();
}
