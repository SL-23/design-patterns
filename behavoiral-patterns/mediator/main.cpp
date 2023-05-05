#include <iostream>
#include <string>
#include <vector>

using namespace std;

class BaseComponent;

class Mediator
{
public:
  virtual void Notify(BaseComponent *sender, string event) = 0;
};

class BaseComponent
{
protected:
  Mediator *mediator_;

public:
  BaseComponent(Mediator *mediator = nullptr) : mediator_(mediator){};

  void set_mediator(Mediator *mediator)
  {
    this->mediator_ = mediator;
  }
};

class SenderComponent1 : public BaseComponent
{
public:
  void DoA()
  {
    cout << "SenderComponent1 does A." << endl;
    this->mediator_->Notify(this, "A");
  }
  void DoB()
  {
    cout << "SenderComponent1 does B." << endl;
    this->mediator_->Notify(this, "B");
  }
};

class SenderComponent2 : public BaseComponent
{
public:
  void DoC()
  {
    cout << "SenderComponent2 does C." << endl;
    this->mediator_->Notify(this, "C");
  }
  void DoD()
  {
    cout << "SenderComponent2 does D." << endl;
    this->mediator_->Notify(this, "D");
  }
};

class ConcreteMediator : public Mediator
{
private:
  SenderComponent1 *sender_component1_;
  SenderComponent2 *sender_component2_;

public:
  ConcreteMediator(SenderComponent1 *sender_component1, SenderComponent2 *sender_component2) : sender_component1_(sender_component1), sender_component2_(sender_component2)
  {
    this->sender_component1_->set_mediator(this);
    this->sender_component2_->set_mediator(this);
  }

  void Notify(BaseComponent *sender, string event)
  {
    if (event == "A")
    {
      cout << "Mediator reacts on A and triggers following operations:" << endl;
      this->sender_component2_->DoC();
    }
    if (event == "D")
    {
      cout << "Mediator reacts on D and triggers following operations:" << endl;
      this->sender_component1_->DoB();
      this->sender_component2_->DoC();
    }
  }
};

void ClientCode()
{
  SenderComponent1 *c1 = new SenderComponent1;
  SenderComponent2 *c2 = new SenderComponent2;

  ConcreteMediator *mediator = new ConcreteMediator(c1, c2);
  cout << "client triggers operation A." << endl;
  c1->DoA();
  cout << endl;

  cout << "client triggers operation B." << endl;
  c1->DoB();
  cout << endl;

  cout << "client triggers operation D." << endl;
  c2->DoD();

  delete c1;
  delete c2;
  delete mediator;
}
int main()
{
  ClientCode();
  return 0;
}