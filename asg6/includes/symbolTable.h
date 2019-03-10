#ifndef _SYMBOLTABLE__H
#define _SYMBOLTABLE__H
#include <algorithm>
#include <iostream>
#include <map>
#include <string>

class Literal;

class SymbolTable {
 public:
  const Literal* getValue(const std::string& name) const;
  void setValue(const std::string& name, const Literal* val);
  SymbolTable() : table() {}

 private:
  std::map<std::string, const Literal*> table;
};

#endif
