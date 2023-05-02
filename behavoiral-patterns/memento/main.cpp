#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Memento
{
public:
  virtual ~Memento() {}
  virtual string getName() const = 0;
  virtual string date() const = 0;
  virtual string state() const = 0;
};

class ConcreteMemento : public Memento
{
private:
  string state_;
  string date_;

public:
  ConcreteMemento(string state) : state_(state)
  {
    time_t now = time(0);
    this->date_ = ctime(&now);
  }

  string state() const override
  {
    return this->state_;
  }
  string getName() const override
  {
    return this->date_ + " / (" + this->state_.substr(0, 9) + "...)";
  }
  string date() const override
  {
    return this->date_;
  }
};

class Originator
{
private:
  string state_;
  string GenerateRandomString(int length = 10)
  {
    const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    int stringLength = sizeof(alphanum) - 1;
    string randomString;
    for (int i = 0; i < length; ++i)
    {
      randomString += alphanum[rand() % stringLength];
    }
    return randomString;
  }

public:
  Originator(string state) : state_(state)
  {
    cout << "Originator: my init state is: " << this->state_ << endl;
  }
  void DoSomething()
  {
    cout << "Originator: im doing important stuffs\n";
    this->state_ = this->GenerateRandomString(30);
    cout << "Originator: and my state has changed to: " << this->state_ << endl;
  }
  Memento *Save()
  {
    return new ConcreteMemento(this->state_);
  }
  void Restore(Memento *memento)
  {
    this->state_ = memento->state();
    cout << "Originator: my state has changed to:" << this->state_ << endl;
  }
};

class Caretaker
{
private:
  vector<Memento *> mementos_;
  Originator *originator_;

public:
  Caretaker(Originator *originator) : originator_(originator) {}
  ~Caretaker()
  {
    for (auto m : mementos_)
      delete m;
  }

  void Backup()
  {
    cout << "\nCaretaker: saving originator's state ... \n";
    this->mementos_.push_back(this->originator_->Save());
  }
  void Undo()
  {
    if (!this->mementos_.size())
    {
      return;
    }
    Memento *memento = this->mementos_.back();
    this->mementos_.pop_back();
    cout << "Caretaker: restoring state to: " << memento->getName() << endl;
    try
    {
      this->originator_->Restore(memento);
    }
    catch (...)
    {
      this->Undo();
    }
  }

  void ShowHistory() const
  {
    cout << "Caretaker: here's the list of mementos: \n";
    for (Memento *m : this->mementos_)
    {
      cout << m->getName() << endl;
    }
  }
};

void ClientCode()
{
  Originator *originator = new Originator("sssssuper");
  Caretaker *caretaker = new Caretaker(originator);

  caretaker->Backup();
  originator->DoSomething();
  caretaker->Backup();
  originator->DoSomething();

  cout << endl;

  caretaker->ShowHistory();
  cout << "let's roll back" << endl;
  caretaker->Undo();
  cout << "once more roll back" << endl;
  caretaker->Undo();

  delete originator;
  delete caretaker;
}

int main()
{
  ClientCode();
  return 0;
}