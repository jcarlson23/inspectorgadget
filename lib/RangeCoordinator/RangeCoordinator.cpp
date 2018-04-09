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

#include <iostream>

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
      // anything we want to do upon a branch instruction, we do it here...
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
	if ( Instruction * I = dyn_cast<Instruction>(Condition) ) {
	  
	  if ( Condition ) {
	    
	    std::cerr << "We have a branch condition\n";
	    Condition->dump();

	    // first we want to look up the dependencies
	    MemDepResult Res = MD.getDependency(I);
	    I->dump();
	    
	    // next once we determine them, then we want to see
	    // if we have some sort of comparison and then
	    // obtain the ranges for this comparison.
	    bool isClobber = Res.isClobber();
	    bool isDef     = Res.isDef();
	    bool isNonLocal= Res.isNonLocal();
	    bool isUnknown = Res.isUnknown();
	    
	    if ( isClobber ) {
	      std::cerr << "We have a clobber\n";
	    } else if ( isDef ) {
	      std::cerr << "We have a definition\n";
	    } else if ( isNonLocal ) {
	      std::cerr << "We have a non-local\n";
	    } else if ( isUnknown ) {
	      std::cerr << "We have an unknown\n";
	    }
	   
	    
	    // if so we look at the dependency to see what ranges of
	    // the variable suggest a domain.  This effectively coordinates the
	    // range of a variable to access a given basic block.
	    // once this is done, we need to asses what block dependencies
	    // are disjoint from others.
	    
	  }
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
