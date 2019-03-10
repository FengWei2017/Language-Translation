#include "poolOfNodes.h"
#include "node.h"
#include "symbolTable.h"

PoolOfNodes& PoolOfNodes::getInstance() {
  static PoolOfNodes pool;
  return pool;
}

void PoolOfNodes::drainThePool() {
  for (const Node* node : nodePool) {
    delete node;
  }

  for (const std::vector<Node*>* vec : vectorPool) {
    delete vec;
  }

  for (const SymbolTable* st : stPool) {
    delete st;
  }
}

