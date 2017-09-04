#ifndef _GADGET_EDGE_H_
#define _GADGET_EDGE_H_

class Node;

class Edge {
 public:
  // constructor for defined edges at construction time
  Edge(const Node* A, const Node* B);

  // constructor for edges defined at a later time
  Edge() {
    color = Unknown;
    Alpha = Beta = nullptr;
  }

  Edge ( EdgeColor color ) : color(color) {
    Alpha = Beta = nullptr;
  }

  Edge( EdgeColor color, const Node * A, const Node * B) : color(color), Alpha(A), Beta(B) {
  }

  // destructor
  virtual ~Edge() {
    if ( Alpha != nullptr ) {
      delete Alpha;
      Alpha = nullptr;
    }
    if ( Beta != nullptr ) {
      delete Beta;
      Beta = nullptr;
    }
  }

  typedef enum EdgeColor {
    Unknown = 0,
    Red = 1,
    Blue = 2,
  }
  
  // {get set} the Alpha Node (Source)
  Node *Source() { return Alpha; }
  void Source( const Node *A ) { Alpha = A; }
  Node *Destination() { return Beta; }
  void Destinration( const Node *B ) { Beta = B; }

  
  EdgeColor Color( ) {
    return color;
  }

  void Color( EdgeColor color ) {
    color = color;
  }
 
 private:
  Node * Alpha;
  Node * Beta;
  Color color;
  
};

#endif
