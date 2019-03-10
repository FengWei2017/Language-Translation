#ifndef _TABLE_MANAGER_H__
#define _TABLE_MANAGER_H__
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "symbolTable.h"
#include "poolOfNodes.h"

class Node;
class TableManager {
 public:
  static TableManager& getInstance();
  void setSymbolTable();
  void deleteSymbolTable();
  void setValue(std::string name, const Literal* val);
  void setGlobalValue(std::string name, const Literal* val);
  void setFunctionValue(const std::string& name, Node* func);
  void setGlobalFlag(std::string name);
  const Literal* getValue(std::string name) const;
  Node* getFunctionValue(std::string name);
  const Literal* getGlobalValue(std::string name) const;
  bool getGlobalFlag(std::string name) const;
  int funcLevel = 0;
 private:
  std::vector<SymbolTable*> scope;
  std::map<std::string, Node*> function;
  std::map<std::string, bool> global;
  TableManager() {
    SymbolTable* mytable = new SymbolTable();
    scope.push_back(mytable);
    PoolOfNodes::getInstance().addSymbolTable(mytable);
  }
};
#endif