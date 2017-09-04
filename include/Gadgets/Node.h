#ifndef _GADGET_NODE_H_
#define _GADGET_NODE_H_

#include <set>
#include "Gadgets/Edge.h"


#define DEFAULT_INFLOW_CONSTRAINT 2

class Node {

 public:
  Node( unsigned int constraint ) { inflow_constraint = constraint; }
  Node() { inflow_constraint = DEFAULT_INFLOW_CONSTRAINT; }

  std::set<Edge*> edges;

  // calculate the inflow to the node
  unsigned int Inflow(void) {
    unsigned int weight = 0;
    for ( auto &E : edges ) {
      if (E->Destination() == this)
	weight += static_cast<unsigned int>(E->Color());
    }
    return weight;
  }

  // calculate the out flow from the node
  unsigned int OutFlow(void) {
    unsigned int weight = 0;
    for ( auto &E : edges ) {
      if ( E->Destination() != this )
	weight += static_cast<unsigned int>(E->Color());
    }
  }
  
 private:
  unsigned int inflow_constraint;
  
};

#endif
