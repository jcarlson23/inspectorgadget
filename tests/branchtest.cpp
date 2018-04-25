#include <iostream>

int main(int argc, char *argv[]) {

  int value = atoi(argv[2]);
  int result= 0;
  
  if ( value > 2 ) {

    switch( value ) {

    case 3:
      result += 2;
      break;
    case 4:
      result += 3;
      break;
    case 5:
      result += 6;
    default:
      result = 2 * value;
    }
    
  } else {
    if ( value < 0 ) {
      result = 0;
    } else if ( value == 1 ) {
      result = value;
    }
    
  }

  std::cout << "Resultant becomes " << result << "\n";
  return 0;
}
