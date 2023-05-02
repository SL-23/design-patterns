#include <iostream>
#include <string>
#include <vector>

using namespace std;

class AbstractClass
{
public:
  void TemplateMethod() const
  {
    this->BaseOperation1();
    this->RequiredOperations1();
    this->BaseOperation2();
    this->Hook1();
    this->RequiredOperation2();
    this->BaseOperation3();
    this->Hook2();
  }

protected:
  void BaseOperation1() const
  {
    cout << "AbstractClass says: I'm doing the bulk of the work\n";
  }
  void BaseOperation2() const
  {
    cout << "AbstractClass says: But i let subclass override some operations\n";
  }
  void BaseOperation3() const
  {
    cout << "AbstractClass says: But im doing the bulk of the work anyway\n";
  }

  virtual void RequiredOperations1() const = 0;
  virtual void RequiredOperation2() const = 0;

  virtual void Hook1() const {}
  virtual void Hook2() const {}
};

class ConcreteClass1 : public AbstractClass
{
protected:
  void RequiredOperations1() const override
  {
    cout << "ConcreteClass1 says: implemented operation1 \n";
  }
  void RequiredOperation2() const override
  {
    cout << "ConcreteClass1 says: implemented operaiton2\n";
  }
};

class ConcreteClass2 : public AbstractClass
{
protected:
  void RequiredOperations1() const override
  {
    cout << "ConcreteClass2 says: implemented operation1\n";
  }
  void RequiredOperation2() const override
  {
    cout << "ConcreteClass2 says: implemented operation2 \n";
  }
  void Hook1() const override
  {
    cout << "ConcreteClass2 says: overridden hook1\n";
  }
};

void ClientCode(AbstractClass *class_)
{
  class_->TemplateMethod();
}

int main()
{
  cout << "Same client code can work with different subclasses: \n";
  ConcreteClass1 *cc1 = new ConcreteClass1;
  ConcreteClass2 *cc2 = new ConcreteClass2;

  ClientCode(cc1);
  cout << endl
       << endl;
  ClientCode(cc2);

  delete cc1;
  delete cc2;
  return 0;
}