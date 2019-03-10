#include <iostream>
#include <typeinfo>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include "ast.h"
#include "symbolTable.h"
#include "tableManager.h"

int elifflg=0;

const Literal* IdentNode::eval() const { 
  const Literal* val = TableManager::getInstance().getValue(ident);
  return val;
}

AsgBinaryNode::AsgBinaryNode(Node* left, Node* right) : 
  BinaryNode(left, right) { 
  const Literal* res = right->eval();
  const std::string n = static_cast<IdentNode*>(left)->getIdent();
  TableManager::getInstance().setValue(n, res);
}


const Literal* AsgBinaryNode::eval() const { 
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* res = right->eval();

  const std::string n = static_cast<IdentNode*>(left)->getIdent();
  TableManager::getInstance().setValue(n, res);
  return res;
}

const Literal* AddBinaryNode::eval() const { 
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return (*x+*y);
}

const Literal* SubBinaryNode::eval() const { 
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return ((*x)-(*y));
}

const Literal* MulBinaryNode::eval() const { 
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return ((*x)*(*y));
}

const Literal* DivBinaryNode::eval() const { 
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return ((*x)/(*y));
}

//asg4

const Literal* PerBinaryNode::eval() const { 
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return ((*x)%(*y));
}

const Literal* DoubleDivBinaryNode::eval() const { 
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return ((*x).doubleDiv(*y));
}

const Literal* PowBinaryNode::eval() const { 
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return ((*x).myPow(*y));
}

const Literal* SliceNode::eval() const { 
 
  const Literal* x = str->eval();
  std::vector<int> a;
  for(int i = 0; i<(*location).size(); i++){
     a.push_back((*location)[i]->eval()->getVal());   
   }
  return ((*x)[a]);
}

//asg5

const Literal* FuncNode::eval() const {
  const std::string id = static_cast<IdentNode*>(funcName)->getIdent();
  const Literal* res = nullptr;
  std::vector<Node*>::iterator it = suite->begin();
  while (it != suite->end()) {
    res = (*it)->eval();
    const Literal* l = TableManager::getInstance().getValue("RETURN");
    if (l != nullptr) break;
    it++;
  }
  return res ? res : nullptr;
}

const Literal* PrintNode::eval() const {
  if (right == nullptr)
    //std::cout << std::endl;
    ;
  else {
    const Literal* res = right->eval();
    if (res->getVal() == 1000000000)
      std::cout << "None" << std::endl;
    else {
      try {
        res->eval()->print();
        //std::cout << std::endl;
      } catch (const std::string& msg) {
        std::cout << "oops: " << msg << std::endl;
      }
    }
  }
  return nullptr;
}
// This doesn't work very well
const Literal* GlobalNode::eval() const {
  std::vector<Node*>::iterator it = vec->begin();
  while (it != vec->end()) {
    const std::string id = static_cast<IdentNode*>(*it)->getIdent();
    const Literal* res = TableManager::getInstance().getGlobalValue(id);
    if (res != nullptr) TableManager::getInstance().setGlobalValue(id, res);
    TableManager::getInstance().setGlobalFlag(id);
    it++;
  }
  return nullptr;
}

const Literal* ReturnNode::eval() const {
  const Literal* res = nullptr;
  right ? res = right->eval() : res = new IntLiteral(1000000000);
  TableManager::getInstance().setValue("RETURN", res);
  return res;
}

const Literal* BreakNode::eval() const {
  const Literal* res = new IntLiteral(1000000000);
  TableManager::getInstance().setValue("BREAK", res);
  return res;
}

const Literal* SuiteNode::eval() const {
  if (!left || !right) {
    throw std::string("error");
  }
  Node* res = new AsgBinaryNode(left, right);
  PoolOfNodes::getInstance().add(res);
  return nullptr;
}


const Literal* CallNode::eval() const {
  TableManager::getInstance().funcLevel += 1;
  const std::string id = static_cast<IdentNode*>(funcName)->getIdent();
  Node* func = TableManager::getInstance().getFunctionValue(id);
  TableManager::getInstance().setSymbolTable();
  std::vector<Node*>* vec = static_cast<FuncNode*>(func)->getParameters();
  if (vec->size() == parameters->size()) {
    std::vector<Node*>::const_iterator it1 = vec->begin();
    std::vector<Node*>::const_iterator it2 = parameters->begin();
    while (it1 != vec->end()) {
      const std::string id = static_cast<IdentNode*>(*it1)->getIdent();
      const Literal* res = (*it2)->eval();
      TableManager::getInstance().setValue(id, res);
      it1++;
      it2++;
    }
  }

  const Literal* res = func->eval();
  TableManager::getInstance().deleteSymbolTable();
  TableManager::getInstance().funcLevel -= 1;
  return res ? res : nullptr;
}

const Literal* IfNode::eval() const {

  const Literal* if_test = test->eval();
  float val = if_test->getVal();
  if (val) {
    std::vector<Node*>::iterator it = left->begin();
    const Literal* res = nullptr;
    while (it != left->end()) {
      res = (*it)->eval();
      if (res != nullptr) return res;
      it++;
    }
  } 
  else if (elif_node != nullptr) {
    const Literal* res = nullptr;
    std::vector<Node*>::iterator it = elif_node->begin();
    while (it != elif_node->end()) {
      res = (*it)->eval();
      if (res != nullptr) return res;
      it++;
    }
  }  
  if (right != nullptr && !val && !elifflg) {
    std::vector<Node*>::iterator it = right->begin();
    const Literal* res = nullptr;
    while (it != right->end()) {
      res = (*it)->eval();
      if (res != nullptr) return res;
      it++;
    }
  }
  elifflg=0;
  return nullptr;
}

const Literal* ElifNode::eval() const {
  const Literal* if_test = test->eval();
  float val = if_test->getVal();
  if (val) {
    elifflg=1;
    std::vector<Node*>::iterator it = left->begin();
    const Literal* res = nullptr;
    while (it != left->end()) {
      res = (*it)->eval();
      if (res != nullptr) return res;
      ;
      it++;
    }
  }

  return nullptr;
 
}

const Literal* WhileNode::eval() const {
  while (test->eval()->getVal()) {
    std::vector<Node*>::iterator it = left->begin();
    const Literal* res = nullptr;
    int x = 0;
    while (it != left->end()) {
      res = (*it)->eval();
      if (res != nullptr) break;
      const Literal* l = TableManager::getInstance().getValue("BREAK");
      if (l != nullptr) {
        x = 1;
        break;
      }
      it++;
    }
    if (x == 1)
      break;
    else if ((test->eval()->getVal()) != 0)
      continue;
    return res;
  }
  return nullptr;
}

const Literal* LessBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* res = nullptr;
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  if ((((*x) > (*y)))->getVal()) {
    res = new BoolLiteral(false);
  } else if ((((*x) == (*y)))->getVal()) {
    res = new BoolLiteral(false);
  } else {
    res = new BoolLiteral(true);
  }

  PoolOfNodes::getInstance().add(res);
  return res;
}

const Literal* LessEqualBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* res = nullptr;
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  (((*x) > (*y)))->getVal() ? res = new BoolLiteral(false) : res = new BoolLiteral(true);
  PoolOfNodes::getInstance().add(res);
  return res;
}

const Literal* GreaterBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return ((*x) > (*y));
}

const Literal* GreaterEqualBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* res = nullptr;
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  if ((((*x) > (*y)))->getVal()) {
    res = new BoolLiteral(true);
  } else if ((((*x) == (*y)))->getVal()) {
    res = new BoolLiteral(true);
  } else {
    res = new BoolLiteral(false);
  }
  PoolOfNodes::getInstance().add(res);
  return res;
}

const Literal* EqEqualBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return ((*x) == (*y));
}

const Literal* NotEqualBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* res = nullptr;
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  (((*x) == (*y)))->getVal() ? res = new BoolLiteral(false) : res = new BoolLiteral(true);
  PoolOfNodes::getInstance().add(res);
  return res;
}
