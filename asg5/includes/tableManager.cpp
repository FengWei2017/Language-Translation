#include <cstdlib>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include "literal.h"
#include "tableManager.h"

TableManager& TableManager::getInstance() {
  static TableManager instance;
  return instance;
}
void TableManager::setSymbolTable() {
  SymbolTable* st = new SymbolTable();
  scope.push_back(st);
  PoolOfNodes::getInstance().addSymbolTable(st);
}
void TableManager::deleteSymbolTable() { scope.pop_back(); }

const Literal* TableManager::getValue(std::string name) const {
  if (funcLevel != 1) {
    std::vector<SymbolTable*>::const_reverse_iterator it = scope.rbegin();
    while (it != scope.rend()) {
      const Literal* res = (*it)->SymbolTable::getValue(name);
      if (res != NULL) return res;
      it++;
    }
  } else {
    const Literal* rhs = scope.back()->SymbolTable::getValue(name);
    if (rhs != NULL) return rhs;
    const Literal* lhs = scope.front()->SymbolTable::getValue(name);
    if (lhs != NULL) return lhs;
  }
  return NULL;
}
void TableManager::setValue(std::string name, const Literal* val) {
  if (TableManager::getInstance().funcLevel == 0) {
    scope.front()->SymbolTable::setValue(name, val);
  } else {
    scope.back()->SymbolTable::setValue(name, val);
  }
}
Node* TableManager::getFunctionValue(std::string name) {
  std::map<std::string, Node*>::const_iterator it = function.find(name);
  if (it == function.end()) throw name + std::string(" not found");
  return it->second;
}
bool TableManager::getGlobalFlag(std::string name) const {
  std::map<std::string, bool>::const_iterator ptr = global.find(name);
  if (ptr == global.end()) {
    return false;
  } else {
    return true;
  }
}
void TableManager::setFunctionValue(const std::string& name, Node* func) { function[name] = func; }
const Literal* TableManager::getGlobalValue(std::string name) const {
  const Literal* res = scope.front()->SymbolTable::getValue(name);
  if (res != NULL) return res;
  return NULL;
}
void TableManager::setGlobalValue(std::string name, const Literal* val) {
  scope.front()->SymbolTable::setValue(name, val);
  scope.back()->SymbolTable::setValue(name, val);
}

void TableManager::setGlobalFlag(std::string name) { global[name] = true; }
