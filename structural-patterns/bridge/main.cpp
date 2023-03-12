#include <iostream>
#include <string>

using namespace std;

class Implementation
{
public:
  virtual ~Implementation() {}
  virtual string OperationImplementation() const = 0;
};

class ConcreteImplementationA : public Implementation
{
public:
  string OperationImplementation() const override
  {
    return "ConcreteImplementationA: result on platform A\n";
  }
};

class ConcreteImplementationB : public Implementation
{
public:
  string OperationImplementation() const override
  {
    return "ConcreteImplementationB: result on platform B\n";
  }
};

class Abstraction
{
protected:
  Implementation *implementaion_;

public:
  Abstraction(Implementation *implementation) : implementaion_(implementation) {}
  virtual ~Abstraction() {}

  virtual string Operation() const
  {
    return "Abstraction: Base operation with:\n" + this->implementaion_->OperationImplementation();
  }
};

class ExtendedAbstration : public Abstraction
{
public:
  ExtendedAbstration(Implementation *implementation) : Abstraction(implementation) {}

  string Operation() const override
  {
    return "ExtendedAbstraction: extended operation with: \n" + this->implementaion_->OperationImplementation();
  }
};

void ClientCode(const Abstraction &abstraction)
{
  cout << abstraction.Operation();
}

int main()
{
  Implementation *implementation = new ConcreteImplementationA;
  Abstraction *abstraction = new Abstraction(implementation);

  ClientCode(*abstraction);
  cout << endl;

  delete implementation;
  delete abstraction;

  implementation = new ConcreteImplementationB;
  abstraction = new ExtendedAbstration(implementation);

  ClientCode(*abstraction);

  delete implementation;
  delete abstraction;
  return 0;
}