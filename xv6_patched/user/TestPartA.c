/*
  @title MiniProject 1
  @summary SystemCall SecondPart Tester
*/

#include "fs.h"
#include "stat.h"
#include "types.h"
#include "user.h"

int main(int argc, char *argv[]) {
  printf(1, RESET "  Use argument \'help\' for the help menu\n\n" RESET);

  if (argc > 2) {
    printf(1, "Only 1 argument is allowed");
    exit();
  } else if (argc == 2) {
    char help[4] = "help";
    char *arg = argv[1];

    if (arg[0] == help[0]) {
      printf(1, "\t" MAGENTA "TestingPartA" BLUE
                "  <-- returns total number of getpid() calls.\n" RESET);
      printf(1, "\t" MAGENTA "TestingPartA <num>" BLUE
                " <-- calls getpid() <num> times.\n" RESET);
      exit();
    } else {
      int loops = atoi(arg);

      for (int i = 0; i < loops; i++) {
        printf(1, GREEN "\t[%d]  -->  " MAGENTA "getpid(): %d" RESET "\n" RESET,
               i, getpid());
      }
    }
    exit();
  } else if (argc == 1) {
    printf(1,
           BLUE "\n  --> Total " MAGENTA "getpid()" BLUE " Calls: %d\n\n" RESET,
           FirstPart());
  }
  exit();
}
