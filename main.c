#include <stdio.h>
#include <unistd.h>

#include "global.h"

void main (int argc, char** argv) {
  initProg ();
  parseExpr(argv[1]);
  double x;
  for (x = 0; x < 1; x+=0.1) {
    genEval(x);
  }
   
}
