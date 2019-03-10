#ifndef _POOLOFNODES__H
#define _POOLOFNODES__H

#include <vector>
class Node;

class Node;
class SymbolTable;

class PoolOfNodes {
 public:
  static PoolOfNodes& getInstance();
  void add(const Node* node) { nodePool.push_back(node); }
  void addVec(const std::vector<Node*>* vec) { vectorPool.push_back(vec); }
  void addSymbolTable(const SymbolTable* v) { stPool.push_back(v); }
  void drainThePool();

 private:
  std::vector<const Node*> nodePool;
  std::vector<const std::vector<Node*>*> vectorPool;
  std::vector<const SymbolTable*> stPool;
  PoolOfNodes() : nodePool(), vectorPool(), stPool() {}
};

#endif