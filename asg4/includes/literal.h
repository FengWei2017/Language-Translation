#include "node.h"
#include "poolOfNodes.h"
#include <cmath>
#include <cfenv>
#include <math.h>
#include <iostream> // std::cout, std::fixed
#include <iomanip>  // std::setprecision
#include <string>

class Literal : public Node
{
public:
  virtual ~Literal() {}

  virtual const Literal *operator+(const Literal &rhs) const = 0;
  virtual const Literal *opPlus(float) const = 0;
  virtual const Literal *opPlus(int) const = 0;
  virtual const Literal *opPlus(std::string ) const = 0;

  virtual const Literal *operator*(const Literal &rhs) const = 0;
  virtual const Literal *opMult(float) const = 0;
  virtual const Literal *opMult(int) const = 0;
  virtual const Literal *opMult(std::string ) const = 0;

  virtual const Literal *operator-(const Literal &rhs) const = 0;
  virtual const Literal *opSubt(float) const = 0;
  virtual const Literal *opSubt(int) const = 0;
  virtual const Literal *opSubt(std::string ) const = 0;

  virtual const Literal *operator/(const Literal &rhs) const = 0;
  virtual const Literal *opDiv(float) const = 0;
  virtual const Literal *opDiv(int) const = 0;
  virtual const Literal *opDiv(std::string ) const = 0;

  virtual const Literal *operator%(const Literal &rhs) const = 0;
  virtual const Literal *opPer(float) const = 0;
  virtual const Literal *opPer(int) const = 0;
  virtual const Literal *opPer(std::string ) const = 0;

  virtual const Literal *operator>(const Literal &rhs) const = 0;
  virtual const Literal *opDoubleDiv(float) const = 0;
  virtual const Literal *opDoubleDiv(int) const = 0;
  virtual const Literal *opDoubleDiv(std::string ) const = 0;

  virtual const Literal *operator<(const Literal &rhs) const = 0;
  virtual const Literal *opPow(float) const = 0;
  virtual const Literal *opPow(int) const = 0;
  virtual const Literal *opPow(std::string ) const = 0;
   

  virtual const Literal *operator[](std::vector<int>  right) const = 0;
  virtual const int getval() const=0;
  virtual const Literal *eval() const = 0;
  virtual void print() const
  {
    std::cout << "No Way" << std::endl;
  }
};


//FLOAT
class FloatLiteral : public Literal
{
public:
  FloatLiteral(float _val) : val(_val) {}

  virtual const Literal *operator+(const Literal &rhs) const
  {
    return rhs.opPlus(val);
  }
  virtual const Literal *opPlus(float lhs) const
  {
    const Literal *node = new FloatLiteral(lhs + val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal *opPlus(int lhs) const
  {
    const Literal *node = new FloatLiteral(lhs + val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal *opPlus(std::string lhs) const
  {
    throw std::string("Can't add float and string");
  }

  virtual const Literal *operator-(const Literal &rhs) const
  {
    return rhs.opSubt(val);
  }
  virtual const Literal *opSubt(float lhs) const
  {
    const Literal *node = new FloatLiteral(lhs - val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal *opSubt(int lhs) const
  {
    const Literal *node = new FloatLiteral(lhs - val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal *opSubt(std::string lhs) const
  {
    throw std::string("Can't Sub float and string");
  }

  virtual const Literal *operator*(const Literal &rhs) const
  {
    return rhs.opMult(val);
  }
  virtual const Literal *opMult(float lhs) const
  {
    const Literal *node = new FloatLiteral(lhs * val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal *opMult(int lhs) const
  {
    const Literal *node = new FloatLiteral(static_cast<float>(lhs) * val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal *opMult(std::string lhs) const
  {
    throw std::string("Can't Mult float and string");
  }

  virtual const Literal *operator/(const Literal &rhs) const
  {
    return rhs.opDiv(val);
  }
  virtual const Literal *opDiv(float lhs) const
  {
    if (val == 0)
      throw std::string("Zero Division Error");
    const Literal *node = new FloatLiteral(lhs / val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal *opDiv(int lhs) const
  {
    if (val == 0)
      throw std::string("Zero Division Error");
    const Literal *node = new FloatLiteral(lhs / val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal *opDiv(std::string lhs) const
  {
    throw std::string("Can't Div float and string");
  }

  virtual const Literal *operator%(const Literal &rhs) const
  {
    return rhs.opPer(val);
  }
  virtual const Literal *opPer(float lhs) const
  {
    if (val == 0)
      throw std::string("Zero Division Error");
    const Literal *node = new FloatLiteral(std::fmod(lhs, val));
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal *opPer(int lhs) const
  {
    if (val == 0)
      throw std::string("Zero Division Error");
    const Literal *node = new FloatLiteral(std::fmod(lhs, val));
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal *opPer(std::string lhs) const
  {
    throw std::string("Can't Percentage float and string");
  }

  virtual const Literal *operator>(const Literal &rhs) const
  {
    return rhs.opDoubleDiv(val);
  }
  virtual const Literal *opDoubleDiv(float lhs) const
  {
    if (val == 0)
      throw std::string("Zero Division Error");
    const Literal *node = new FloatLiteral(floor(lhs / val));
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal *opDoubleDiv(int lhs) const
  {
    if (val == 0)
      throw std::string("Zero Division Error");
    const Literal *node = new FloatLiteral(floor(lhs / val));
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal *opDoubleDiv(std::string lhs) const
  {
    throw std::string("Can't Dive float and string");
  }

  virtual const Literal *operator<(const Literal &rhs) const
  {
    return rhs.opPow(val);
  }
  virtual const Literal *opPow(float lhs) const
  {
    if (lhs < 0 && val > 0 && val < 1)
      throw std::string("Complex number");
    const Literal *node = new FloatLiteral(pow(lhs, val));
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal *opPow(int lhs) const
  {
    if (lhs < 0 && val > 0 && val < 1)
      throw std::string("Complex number");
    const Literal *node = new FloatLiteral(pow(lhs, val));
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal *opPow(std::string lhs) const
  {
    throw std::string("Can't Pow float and string");
  }
  
  virtual const Literal* operator[](std::vector<int> right) const{
    throw std::string("Can't slice float");
  }
  
  virtual const Literal *eval() const { return this; }
  virtual const int getval() const { return 0; }
  virtual void print() const
  {
    if (val - int(val))
    {
      std::cout << "FLOAT: "<< val << std::endl;
    }
    else
    {
      int len = 0;
      int a = int(val);
      while (a)
      {
        a /= 10;
        len++;
      }
      //std::cout << "FLOAT: " << std::setprecision(len) << std::fixed << val << std::endl;
      std::cout << "FLOAT: "<<val<<".0" << std::endl;
    }
  }

private:
  float val;
};


//STRING

class StrLiteral : public Literal
{
public:
  StrLiteral(std::string _val)  { val = _val;}

  virtual const Literal *operator+(const Literal &rhs) const
  {
    return rhs.opPlus(val);
  }
  virtual const Literal *opPlus(float lhs) const
  {
    throw std::string("Erro");
  }
  virtual const Literal *opPlus(int lhs) const
  {
    throw std::string("Erro");
  }
  virtual const Literal *opPlus(std::string lhs) const
  {
    std::string result;
    result=lhs+val;
    const Literal *node = new StrLiteral(result);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal *operator-(const Literal &rhs) const
  {
    return rhs.opSubt(val);
  }
  virtual const Literal *opSubt(float lhs) const
  {
    throw std::string("Erro");
  }
  virtual const Literal *opSubt(int lhs) const
  {
    throw std::string("Erro");
  }
  virtual const Literal *opSubt(std::string lhs) const
  {
    throw std::string("Erro");
  }

  virtual const Literal *operator*(const Literal &rhs) const
  {
    return rhs.opMult(val);
  }
  virtual const Literal *opMult(float lhs) const
  {
    throw std::string("Erro");
  }
  virtual const Literal *opMult(int lhs) const
  {
    std::string result;
    for (int i = 0; i < lhs; i++)
    {
      result+=val;
    }
    const Literal *node = new StrLiteral(result);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal *opMult(std::string lhs) const
  {
    throw std::string("Erro");
  }

  virtual const Literal *operator/(const Literal &rhs) const
  {
    return rhs.opDiv(val);
  }
  virtual const Literal *opDiv(float lhs) const
  {
    throw std::string("Erro");
  }
  virtual const Literal *opDiv(int lhs) const
  {
    throw std::string("Erro");
  }
  virtual const Literal *opDiv(std::string lhs) const
  {
    throw std::string("Erro");
  }

  virtual const Literal *operator%(const Literal &rhs) const
  {
    return rhs.opPer(val);
  }
  virtual const Literal *opPer(float lhs) const
  {
    throw std::string("Erro");
  }
  virtual const Literal *opPer(int lhs) const
  {
    throw std::string("Erro");
  }
  virtual const Literal *opPer(std::string lhs) const
  {
    throw std::string("Erro");
  }

  virtual const Literal *operator>(const Literal &rhs) const
  {
    return rhs.opDoubleDiv(val);
  }
  virtual const Literal *opDoubleDiv(float lhs) const
  {
    throw std::string("Erro");
  }
  virtual const Literal *opDoubleDiv(int lhs) const
  {
    throw std::string("Erro");
  }
  virtual const Literal *opDoubleDiv(std::string lhs) const
  {
    throw std::string("Erro");
  }

  virtual const Literal *operator<(const Literal &rhs) const
  {
    return rhs.opPow(val);
  }
  virtual const Literal *opPow(float lhs) const
  {
    throw std::string("Erro");
  }
  virtual const Literal *opPow(int lhs) const
  {
    throw std::string("Erro");
  }
  virtual const Literal *opPow(std::string lhs) const
  {
    throw std::string("Erro");
  }
  
 
   virtual const Literal* operator[](std::vector<int>  right) const{
    std::string result;
    int start=0, len=1, step=1, strlen=val.size();
    if(right.size()==1){
      start=right[0];
      if(start<0) start+=strlen;
      if(start>strlen) start-=strlen;
    }
    if(right.size()==2){
      start=right[0];
      while(start<0) start+=strlen;
      while(start>strlen) start-=strlen;
      len=right[1];
      while(len<0) len+=strlen;
      len-=start;
    }
     
    result= val.substr(start,len);
    const Literal *node = new StrLiteral(result);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  
  virtual const Literal *eval() const { return this; }
  virtual const int getval() const { return 0; }
  virtual void print() const
  {
    std::cout << "String: " << val << std::endl;
  }

private:
  std::string val;
};


//INT

class IntLiteral : public Literal
{
public:
  IntLiteral(int _val) : val(_val) {}

  virtual const Literal *operator+(const Literal &rhs) const
  {
    return rhs.opPlus(val);
  }
  virtual const Literal *opPlus(float lhs) const
  {
    const Literal *node = new FloatLiteral(static_cast<float>(val) + lhs);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal *opPlus(int lhs) const
  {
    const Literal *node = new IntLiteral(lhs + val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal *opPlus(std::string lhs) const
  {
    throw std::string("Can't Plus int and string");
  }
  virtual const Literal *operator-(const Literal &rhs) const
  {
    return rhs.opSubt(val);
  }
  virtual const Literal *opSubt(float lhs) const
  {
    const Literal *node = new FloatLiteral(lhs - val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal *opSubt(int lhs) const
  {
    const Literal *node = new IntLiteral(lhs - val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal *opSubt(std::string lhs) const
  {
    throw std::string("Can't sub int and string");
  }

  virtual const Literal *operator*(const Literal &rhs) const
  {
    return rhs.opMult(val);
  }
  virtual const Literal *opMult(float lhs) const
  {
    const Literal *node = new FloatLiteral(lhs * val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal *opMult(int lhs) const
  {
    const Literal *node = new IntLiteral(lhs * val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal *opMult(std::string lhs) const
  {
    std::string result;
    for (int i = 0; i < val; i++)
    {
      result += lhs;
    }
    const Literal *node = new StrLiteral(result);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal *operator/(const Literal &rhs) const
  {
    return rhs.opDiv(val);
  }
  virtual const Literal *opDiv(float lhs) const
  {
    if (val == 0)
      throw std::string("Zero Division Error");
    const Literal *node = new FloatLiteral(lhs / val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal *opDiv(int lhs) const
  {
    if (val == 0)
      throw std::string("Zero Division Error");
    const Literal *node = new IntLiteral(lhs / val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal *opDiv(std::string lhs) const
  {
    throw std::string("Can't Div int and string");
  }

  virtual const Literal *operator%(const Literal &rhs) const
  {
    return rhs.opPer(val);
  }
  virtual const Literal *opPer(float lhs) const
  {
    if (val == 0)
      throw std::string("Zero Division Error");
    const Literal *node = new FloatLiteral(std::fmod(lhs, val));
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal *opPer(int lhs) const
  {
    if (val == 0)
      throw std::string("Zero Division Error");
    const Literal *node = new IntLiteral(lhs % val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal *opPer(std::string lhs) const
  {
    throw std::string("Can't Per int and string");
  }

  virtual const Literal *operator>(const Literal &rhs) const
  {
    return rhs.opDoubleDiv(val);
  }
  virtual const Literal *opDoubleDiv(float lhs) const
  {
    if (val == 0)
      throw std::string("Zero Division Error");
    const Literal *node = new FloatLiteral(floor(lhs / val));
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal *opDoubleDiv(int lhs) const
  {
    if (val == 0)
      throw std::string("Zero Division Error");
    const Literal *node = new IntLiteral(floor(lhs / val));
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal *opDoubleDiv(std::string lhs) const
  {
    throw std::string("Can't Div int and string");
  }

  virtual const Literal *operator<(const Literal &rhs) const
  {
    return rhs.opPow(val);
  }
  virtual const Literal *opPow(float lhs) const
  {
    if (lhs < 0 && val > 0 && val < 1)
      throw std::string("Complex number");
    const Literal *node = new FloatLiteral(pow(lhs, val));
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal *opPow(int lhs) const
  {
    if (lhs < 0 && val > 0 && val < 1)
      throw std::string("Complex number");
    else if (val >= 0)
    {
      const Literal *node = new IntLiteral(pow(lhs, val));
      PoolOfNodes::getInstance().add(node);
      return node;
    }
    else
    {
      const Literal *node = new FloatLiteral(pow(lhs, val));
      PoolOfNodes::getInstance().add(node);
      return node;
    }
  }
  virtual const Literal *opPow(std::string lhs) const
  {
    throw std::string("Can't Pow int and string");
  }

  virtual const Literal* operator[](std::vector<int> right) const{
    throw std::string("Can't slice int");
  }
 
  virtual const Literal *eval() const { return this; }
  virtual const int getval() const { return val; }
  virtual void print() const
  {
    std::cout << "INT: " << val << std::endl;
  }

private:
  int val;
};
