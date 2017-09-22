#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[] ) {

  int length = argc;
  char x, y;
  if ( length < 2 )
    x = 0;
  else
    x = argv[1][0];

  if ( length < 3 )
    y = 0;
  else
    y = argv[2][0];

  if ( x && y ) {
    printf("Conjunction succeeds\n");
  }

  if ( x || y ) {
    printf("Disjunction\n");
  }

  if ( !x ) {
    printf("Negation\n");
  }
  
  return 0;
  
}
