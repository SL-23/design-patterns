#include <algorithm>
#include <iostream>
#include <list>
#include <string>

using namespace std;

class Subsystem1
{
public:
  string Operation1() const
  {
    return "Subsystem1: ready!\n";
  }

  string OperationN() const
  {
    return "Subsystem1: go\n";
  }
};

class Subsystem2
{
public:
  string Operation1() const
  {
    return "Subsystem2: ready!\n";
  }

  string OperationZ() const
  {
    return "Subsystem2: fire\n";
  }
};

class Facade
{
protected:
  Subsystem1 *subsystem1_;
  Subsystem2 *subsystem2_;

public:
  Facade(Subsystem1 *subsystem1 = nullptr, Subsystem2 *subsystem2 = nullptr)
  {
    this->subsystem1_ = subsystem1 ?: new Subsystem1;
    this->subsystem2_ = subsystem2 ?: new Subsystem2;
  }

  ~Facade()
  {
    delete subsystem1_;
    delete subsystem2_;
  }

  string Operation()
  {
    string result = "Facade initialises subsystems: \n";

    result += this->subsystem1_->Operation1();
    result += this->subsystem2_->Operation1();

    result += "Facade orders subsystems to perform actions:\n";

    result += this->subsystem1_->OperationN();
    result += this->subsystem2_->OperationZ();

    return result;
  }
};

void ClientCode(Facade *facade)
{
  cout << facade->Operation() << endl;
}

int main()
{
  Subsystem1 *sub1 = new Subsystem1;
  Subsystem2 *sub2 = new Subsystem2;
  Facade *facade = new Facade(sub1, sub2);

  ClientCode(facade);
  return 0;
}