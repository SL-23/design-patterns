#include <iostream>
#include <string>
using namespace std;

class AbstractProductA
{
public:
  virtual ~AbstractProductA(){};
  virtual string UsefulFunctionA() const = 0;
};

class ConcreteProductA1 : public AbstractProductA
{
public:
  string UsefulFunctionA() const override
  {
    return "This is product A1";
  }
};

class ConcreteProductA2 : public AbstractProductA
{
public:
  string UsefulFunctionA() const override
  {
    return "This is product A2";
  }
};

class AbstractProductB
{
public:
  virtual ~AbstractProductB() {}
  virtual string UsefulFunctionB() const = 0;

  virtual string AnotherUsefulFunctionB(const AbstractProductA &collaborator) const = 0;
};

class ConcreteProductB1 : public AbstractProductB
{
public:
  string UsefulFunctionB() const override
  {
    return "This is product B1";
  }

  string AnotherUsefulFunctionB(const AbstractProductA &collaberator) const override
  {
    string result = collaberator.UsefulFunctionA();
    return "This is B1 collaborating with " + result;
  }
};

class ConcreteProductB2 : public AbstractProductB
{
public:
  string UsefulFunctionB() const override
  {
    return "This is product B2";
  }

  string AnotherUsefulFunctionB(const AbstractProductA &collaberator) const override
  {
    string result = collaberator.UsefulFunctionA();
    return "This is B2 collaberating with " + result;
  }
};

class AbstractFactory
{
public:
  virtual AbstractProductA *createProductA() const = 0;
  virtual AbstractProductB *createProductB() const = 0;
};

class ConcreteFactory1 : public AbstractFactory
{
public:
  AbstractProductA *createProductA() const override
  {
    return new ConcreteProductA1();
  }

  AbstractProductB *createProductB() const override
  {
    return new ConcreteProductB1();
  }
};

class ConcreteFactory2 : public AbstractFactory
{
public:
  AbstractProductA *createProductA() const override
  {
    return new ConcreteProductA2();
  }

  AbstractProductB *createProductB() const override
  {
    return new ConcreteProductB2();
  }
};

void clientCode(const AbstractFactory &factory)
{
  const AbstractProductA *absProductA = factory.createProductA();
  const AbstractProductB *absProductB = factory.createProductB();

  cout << absProductB->UsefulFunctionB() << endl;
  cout << absProductB->AnotherUsefulFunctionB(*absProductA) << endl;

  delete absProductA;
  delete absProductB;
}

int main()
{
  cout << "Test factory 1:" << endl;
  ConcreteFactory1 *factory1 = new ConcreteFactory1();
  clientCode(*factory1);
  delete factory1;

  cout << "Test factory 2:" << endl;
  ConcreteFactory2 *factory2 = new ConcreteFactory2();
  clientCode(*factory2);
  delete factory2;

  return 0;
}