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
#include "llvm/IR/InstVisitor.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include "llvm/Transforms/Utils/Cloning.h"
#include "llvm/IR/Dominators.h"
#include "llvm/Analysis/MemoryDependenceAnalysis.h"

using namespace llvm;



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
  // RangeInstructionHandler
  struct BranchHandlerVisitor : public InstVisitor<BranchHandlerVisitor> {
    void visitBranchInst(BranchInst &I) {
      outs() << "Branch instruction\n ";
      I.dump();
    }
  };

  
  // ===============================================
  // RangeHandlerPass
  struct RangeHandlerPass : public FunctionPass {

    static char ID;

    RangeHandlerPass() : FunctionPass(ID) {}

    void getAnalysisUsage(AnalysisUsage &AU) const {
      AU.setPreservesCFG();
      AU.addRequired<DominatorTreeWrapperPass>();
      AU.addRequired<MemoryDependenceWrapperPass>();
    }
    
    bool runOnFunction(Function& F) {
      // first get the dominator tree
      auto &DT = getAnalysis<DominatorTreeWrapperPass>().getDomTree();
      auto &MD = getAnalysis<MemoryDependenceWrapperPass>().getMemDep();
      
      for ( auto &BasicBlock : F ) {

	const BranchInst * BI = dyn_cast<BranchInst>(BasicBlock.getTerminator());

	if ( !BI )
	  continue;
	
	BI->dump();

	if ( !BI || !BI->isConditional())
	  continue;

	// lookup MemoryDependenceResults to get the appropriate call syntax.
	Value * Condition = BI->getCondition();
	if ( Condition ) {
	  Condition->dump();
	  MemDepResult &Res = MD.getDependency(Condition);
	  
	}
	else {
	  outs() << "No dependent condition\n";
	}
	
      }
      
      BranchHandlerVisitor Visitor;
      if ( F.isDeclaration() ) {
	return false;
      }

      if ( F.hasName() ) {
	outs() << "Visiting " << F.getName() << "\n";
      } else {
	outs() << "Unnamed Function \n";
      }

      Visitor.visit(F);
      outs() << "\n";
      
      return false;
    }
    
  };

  char RangeHandlerPass::ID = 0;

  


static RegisterPass<RangeHandlerPass> XX("branch-visit","Branch visitor");
