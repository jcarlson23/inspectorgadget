#ifndef _JOINT_ANALYSIS_H_
#define _JOINT_ANALYSIS_H_

#include <algorithm>
#include <memory>
#include <string>
#include <llvm/ADT/SmallVector.h>



class Domain {

 public:
  Domain(void) {
  }

  ~Domain() {}

  private:

  static const unsigned DefaultVariableN = 12;
  std::string _name;

  typedef llvm::SmallVector<std::string,DefaultVariableN> NameVector;

  
};

#endif
