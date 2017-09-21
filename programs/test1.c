#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  int x, y;
  x = atoi( argv[1] );
  
  if ( (x >= 5) && (x <= 20)) {
    y = x*x;
    x = x+1;
    printf("%d\n", y); }
  else {
    y = (x-1)*(x-1);
    x = x-1;
    printf("%d\n",x);
  }

  return 0;
}
