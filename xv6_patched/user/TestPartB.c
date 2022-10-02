/*
  @title MiniProject 1
  @summary SystemCall SecondPart Tester
*/

#include "fs.h"
#include "stat.h"
#include "types.h"
#include "user.h"

int main(void) {
  printf(1, BLUE "\n  --> Total System Calls: %d\n\n" RESET, SecondPart());
  exit();
}