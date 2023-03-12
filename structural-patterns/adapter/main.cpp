#include <iostream>
#include <string>

using namespace std;

class Target
{
public:
  virtual ~Target() = default;

  virtual string Request() const
  {
    return "Targe: the default target's behaviour";
  }
};

class Adaptee
{
public:
  string SpecificRequest() const
  {
    return ".eetpadA eht fo roivaheb laicepS";
  }
};
/****
-- normal inheritance --
class Adapter : public Target
{
private:
  Adaptee *adaptee_;

public:
  Adapter(Adaptee *adaptee) : adaptee_(adaptee) {}
  string Request() const override
  {
    string to_reverse = this->adaptee_->SpecificRequest();
    reverse(to_reverse.begin(), to_reverse.end());

    return "Adapter: " + to_reverse;
  }
};
*****/

// Multiple inheritance

class Adapter : public Target, public Adaptee
{
public:
  Adapter() {}

  string Request() const override
  {
    string to_reverse = SpecificRequest();
    reverse(to_reverse.begin(), to_reverse.end());

    return "Adapter: " + to_reverse;
  }
};

void ClientCode(const Target *target)
{
  cout << target->Request();
}

int main()
{
  cout << "work with target objects:\n";
  Target *target = new Target;
  ClientCode(target);

  cout << endl
       << endl;

  cout << "look at adaptee only:\n";
  Adaptee *adaptee = new Adaptee();
  cout << adaptee->SpecificRequest() << endl
       << endl;

  cout << "work with adapter:\n";
  // old -- Adapter *adapter = new Adapter(adaptee);
  Adapter *adapter = new Adapter();
  ClientCode(adapter);

  return 0;
}