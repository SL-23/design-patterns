#include <algorithm>
#include <iostream>
#include <list>
#include <string>

using namespace std;

class Component
{
public:
  virtual ~Component() {}
  virtual string Operation() const = 0;
};

class ConcreteComponent : public Component
{
public:
  string Operation() const override
  {
    return "ConcreteComponent";
  }
};

class Decorator : public Component
{
protected:
  Component *component_;

public:
  Decorator(Component *component) : component_(component) {}

  string Operation() const override
  {
    return this->component_->Operation();
  }
};

class ConcreteDecoratorA : public Decorator
{
public:
  ConcreteDecoratorA(Component *component) : Decorator(component) {}
  string Operation() const override
  {
    return "ConcreteDecoratorA(" + Decorator::Operation() + ")";
  }
};

class ConcreteDecoratorB : public Decorator
{
public:
  ConcreteDecoratorB(Component *component) : Decorator(component) {}
  string Operation() const override
  {
    return "ConcreteDecoratorB(" + Decorator::Operation() + ")";
  }
};

void ClientCode(Component *component)
{
  cout << "Result: " << component->Operation() << endl;
}

int main()
{
  Component *simple = new ConcreteComponent;
  cout << "Client: simple component" << endl;
  ClientCode(simple);
  cout << endl;

  Component *decorator1 = new ConcreteDecoratorA(simple);
  cout << "Now I decorate the simple component: " << endl;
  ClientCode(decorator1);
  cout << endl;

  Component *decorator2 = new ConcreteDecoratorB(decorator1);
  cout << "Now I decorate decorator 1 hahaha:" << endl;
  ClientCode(decorator2);

  delete simple;
  delete decorator1;
  delete decorator2;

  return 0;
}
