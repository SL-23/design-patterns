#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ConcreteComponentA;
class ConcreteComponentB;

class Visitor
{
public:
  virtual void VisitConcreteComponentA(const ConcreteComponentA *element) const = 0;
  virtual void VisitConcreteComponentB(const ConcreteComponentB *element) const = 0;
};

class Component
{
public:
  virtual ~Component() {}
  virtual void Accept(Visitor *visitor) const = 0;
};

class ConcreteComponentA : public Component
{
public:
  void Accept(Visitor *visitor) const override
  {
    visitor->VisitConcreteComponentA(this);
  }
  string ExclusiveMethodOfConcreteComponentA() const
  {
    return "A";
  }
};

class ConcreteComponentB : public Component
{
public:
  void Accept(Visitor *visitor) const override
  {
    visitor->VisitConcreteComponentB(this);
  }
  string SpecialMethodConcreteComponentB() const
  {
    return "B";
  }
};

class ConcreteVisitor1 : public Visitor
{
  void VisitConcreteComponentA(ConcreteComponentA const *element) const override
  {
    cout << element->ExclusiveMethodOfConcreteComponentA() << " + concrete visitor 1\n ";
  }
  void VisitConcreteComponentB(ConcreteComponentB const *element) const override
  {
    cout << element->SpecialMethodConcreteComponentB() << " + concrete visitor 1\n";
  }
};

class ConcreteVisitor2 : public Visitor
{
  void VisitConcreteComponentA(ConcreteComponentA const *element) const override
  {
    cout << element->ExclusiveMethodOfConcreteComponentA() << " + concrete visitor 2\n ";
  }
  void VisitConcreteComponentB(ConcreteComponentB const *element) const override
  {
    cout << element->SpecialMethodConcreteComponentB() << " + concrete visitor 2\n";
  }
};

void ClientCode(array<const Component *, 2> components, Visitor *visitor)
{
  for (const Component *comp : components)
  {
    comp->Accept(visitor);
  }
}

int main()
{
  array<const Component *, 2> components = {new ConcreteComponentA, new ConcreteComponentB};

  ConcreteVisitor1 *v1 = new ConcreteVisitor1;
  ConcreteVisitor2 *v2 = new ConcreteVisitor2;

  ClientCode(components, v1);
  ClientCode(components, v2);

  for (const Component *comp : components)
  {
    delete comp;
  }

  delete v1;
  delete v2;

  return 0;
}