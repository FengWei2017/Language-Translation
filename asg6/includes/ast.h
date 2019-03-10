#pragma once

//  Declarations for a calculator that builds an AST
//  and a graphical representation of the AST.
//  by Brian Malloy

#include <iostream>
#include <string>
#include <map>
#include "literal.h"
#include <vector>

extern void yyerror(const char*);
extern void yyerror(const char*, const char);


class IdentNode : public Node {
public:
  IdentNode(const std::string id) : Node(), ident(id) { } 
  virtual ~IdentNode() {}
  const std::string getIdent() const { return ident; }
  virtual const Literal* eval() const;
private:
  std::string ident;
};

class BinaryNode : public Node {
public:
  BinaryNode(Node* l, Node* r) : Node(), left(l), right(r) {}
  virtual const Literal* eval() const = 0;
  Node* getLeft()  const { return left; }
  Node* getRight() const { return right; }
  BinaryNode(const BinaryNode&) = delete;
  BinaryNode& operator=(const BinaryNode&) = delete;
protected:
  Node *left;
  Node *right;
};

class AsgBinaryNode : public BinaryNode {
public:
  AsgBinaryNode(Node* left, Node* right);
  virtual const Literal* eval() const;
};

class AddBinaryNode : public BinaryNode {
public:
  AddBinaryNode(Node* left, Node* right) : BinaryNode(left, right) { }
  virtual const Literal* eval() const;
};

class SubBinaryNode : public BinaryNode {
public:
  SubBinaryNode(Node* left, Node* right) : BinaryNode(left, right) { }
  virtual const Literal* eval() const;
};

class MulBinaryNode : public BinaryNode {
public:
  MulBinaryNode(Node* left, Node* right) : BinaryNode(left, right) {}
  virtual const Literal* eval() const;
};

class DivBinaryNode : public BinaryNode {
public:
  DivBinaryNode(Node* left, Node* right) : BinaryNode(left, right) { }
  virtual const Literal* eval() const;
};

// asg 4
class PerBinaryNode : public BinaryNode {
public:
  PerBinaryNode(Node* left, Node* right) : BinaryNode(left, right) { }
  virtual const Literal* eval() const;
};

class DoubleDivBinaryNode : public BinaryNode {
public:
  DoubleDivBinaryNode(Node* left, Node* right) : BinaryNode(left, right) { }
  virtual const Literal* eval() const;
};

class PowBinaryNode : public BinaryNode {
public:
  PowBinaryNode(Node* left, Node* right) : BinaryNode(left, right) { }
  virtual const Literal* eval() const;
};

class SliceNode : public Node {
public:
  SliceNode(Node* left, std::vector<Node*> * right): Node(), str(left), location(right){ }
  virtual const Literal* eval() const;
private:
   Node * str;
   std::vector<Node*> * location;
};

//asg 5
class FuncNode : public Node {
 public:
  FuncNode(Node* l, std::vector<Node*>* p, std::vector<Node*>* r, int scope)
      : Node(), funcName(l), parameters(p), suite(r), scope(scope) {}
  const std::string getName() const { return static_cast<IdentNode*>(funcName)->getIdent(); }
  virtual const Literal* eval() const;
  std::vector<Node*>* getParameters() { return parameters; }

 private:
  Node* funcName;
  std::vector<Node*>* parameters;
  std::vector<Node*>* suite;
  int scope;
};

class PrintNode : public Node {
 public:
  PrintNode(Node* r) : Node(), right(r) {}
  virtual const Literal* eval() const;

 private:
  Node* right;
};

class GlobalNode : public Node {
 public:
  GlobalNode(std::vector<Node*>* v) : Node(), vec(v) {}
  virtual const Literal* eval() const;

 private:
  std::vector<Node*>* vec;
};

class ReturnNode : public Node {
 public:
  ReturnNode(Node* r) : Node(), right(r) { }
  virtual const Literal* eval() const;
  
 private:
  Node* right;
};

class BreakNode : public Node {
 public:
  BreakNode(Node* r) : Node(), right(r) {}
  virtual const Literal* eval() const;

 private:
  Node* right;
};

class SuiteNode : public BinaryNode {
 public:
  SuiteNode(Node* l, Node* r) : BinaryNode(l, r) {}
  virtual const Literal* eval() const;
};

class CallNode : public Node {
 public:
  CallNode(Node* l, std::vector<Node*>* p) : Node(), funcName(l), parameters(p) {}
  virtual const Literal* eval() const;
  int scope;

 private:
  Node* funcName;
  std::vector<Node*>* parameters;
};

class IfNode : public Node {
 public:
  IfNode(Node* t, std::vector<Node*>* l, std::vector<Node*>* s, std::vector<Node*>* r)
      : Node(), test(t), left(l), elif_node(s), right(r) {}
  virtual const Literal* eval() const;
  Node* getTest() { return test; }

 private:
  Node* test;
  std::vector<Node*>* left;
  std::vector<Node*>* elif_node;
  std::vector<Node*>* right;
};

class ElifNode : public Node {
 public:
  ElifNode(Node* t, std::vector<Node*>* l) : Node(), test(t), left(l) {}
  virtual const Literal* eval() const;
  Node* getTest() { return test; }

 private:
  Node* test;
  std::vector<Node*>* left;
};

class WhileNode : public Node {
 public:
  WhileNode(Node* t, std::vector<Node*>* l) : Node(), test(t), left(l) {}
  virtual const Literal* eval() const;

 private:
  Node* test;
  std::vector<Node*>* left;
};

class LessBinaryNode : public BinaryNode {
 public:
  LessBinaryNode(Node* left, Node* right) : BinaryNode(left, right) {}
  virtual const Literal* eval() const;
};

class LessEqualBinaryNode : public BinaryNode {
 public:
  LessEqualBinaryNode(Node* left, Node* right) : BinaryNode(left, right) {}
  virtual const Literal* eval() const;
};

class GreaterBinaryNode : public BinaryNode {
 public:
  GreaterBinaryNode(Node* left, Node* right) : BinaryNode(left, right) {}
  virtual const Literal* eval() const;
};

class GreaterEqualBinaryNode : public BinaryNode {
 public:
  GreaterEqualBinaryNode(Node* left, Node* right) : BinaryNode(left, right) {}
  virtual const Literal* eval() const;
};

class EqEqualBinaryNode : public BinaryNode {
 public:
  EqEqualBinaryNode(Node* left, Node* right) : BinaryNode(left, right) {}
  virtual const Literal* eval() const;
};

class NotEqualBinaryNode : public BinaryNode {
 public:
  NotEqualBinaryNode(Node* left, Node* right) : BinaryNode(left, right) {}
  virtual const Literal* eval() const;
};




