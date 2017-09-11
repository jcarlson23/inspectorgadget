#ifndef _GADGET_OPERATOR_H_
#define _GADGET_OPERATOR_H_

#include <string>

class Operator {
 public:
  Operator(void) {
    type = UNKNOWN;
  }

  Operator(const std::string& opstr) {
    type = _parseOpString( opstr );
  }

  ~Operator() {}

  enum Type {
    CONJUNCTION,
    DISJUNCTION,
    NOACTION,
    UNKNOWN
  };

 private:
  Type type;

 private:
  Type _parseOpString( const std::string& opstr );
  
};

#endif
