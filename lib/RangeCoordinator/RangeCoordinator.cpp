#include <llvm/ADT/Optional.h>
#include "llvm/Analysis/BranchProbabilityInfo.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/Analysis/ScalarEvolutionExpander.h"
#include "llvm/Analysis/ScalarEvolutionExpressions.h"
#include "llvm/IR/Dominators.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/PatternMatch.h"
#include "llvm/Pass.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include "llvm/Transforms/Utils/Cloning.h"
#include "llvm/IR/Dominators.h"

using namespace llvm;

namespace {

  // ===============================================
  // RangeHandler class
  class RangeHandler {

    // analyzed expressions
    const SCEV * Offset = nullptr;
    const SCEV * Scale  = nullptr;

    Value * Length = nullptr;
    Use * CheckUse = nullptr;

  public:
    const SCEV *getOffset() const { return Offset; }
    const SCEV *getScale() const { return Scale; }

    Value * getLength() const { return Length; }

    Use * getCheckUse() const { return CheckUse; }
    
  };
  
  // ===============================================
  // Range class
  class Range {
    const SCEV * Begin;
    const SCEV * End;

  public:
    Range( const SCEV * Begin, const SCEV *End) : Begin(Begin), End(End) {
      assert( Begin->getType() == End->getType() && "ill-typed range!");
    }

    Type * getType() const { return Begin->getType(); }
    const SCEV * getBegin() const { return Begin; }
    const SCEV * getEnd() const { return End; }

    
    
  };


  // ===============================================
  // RangeHandlerPass
  class RangeHandlerPass : public FunctionPass {

    static char ID;

    bool runOnFunction(Function& F) {
      // first get the dominator tree
      auto &DT = getAnalysis<DominatorTreeWrapperPass>().getDomTree();

      const BasicBlock &SB = F.front();
      const BasicBlock &EB = F.back();

      BasicBlockEdge *BE = new BasicBlockEdge(&SB, &EB);
      
      
      return false;
    }
    
  };

  char RangeHandlerPass::ID = 0;
  
}
