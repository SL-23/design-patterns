#include <iostream>
#include <list>
#include <string>

using namespace std;

class IObserver
{
public:
  virtual ~IObserver(){};
  virtual void Update(const string &message_from_subject) = 0;
};

class ISubject
{
public:
  virtual ~ISubject(){};
  virtual void Attach(IObserver *observer) = 0;
  virtual void Detach(IObserver *observer) = 0;
  virtual void Notify() = 0;
};

class Subject : public ISubject
{
private:
  list<IObserver *> list_observer_;
  string message_;

public:
  virtual ~Subject()
  {
    cout << "Goodbye, I was the subject. \n";
  }

  void Attach(IObserver *observer) override
  {
    list_observer_.push_back(observer);
  }
  void Detach(IObserver *observer) override
  {
    list_observer_.remove(observer);
  }

  void CountObserver()
  {
    cout << "There are " << list_observer_.size() << " observers in the list.\n";
  }
  void Notify() override
  {
    list<IObserver *>::iterator itr = list_observer_.begin();
    CountObserver();
    while (itr != list_observer_.end())
    {
      (*itr)->Update(message_);
      ++itr;
    }
  }
  void CreateMessage(string message = "Empty")
  {
    this->message_ = message;
    Notify();
  }

  void SomeBussinessLogic()
  {
    this->message_ = "changed messege!";
    Notify();
    cout << "I'm about to do something important" << endl;
  }
};

class Observer : public IObserver
{
private:
  string message_from_subject_;
  Subject &subject_;
  static int static_number_;
  int number_;

public:
  Observer(Subject &subject) : subject_(subject)
  {
    this->subject_.Attach(this);
    cout << "Hi, i'm the observer \"" << ++static_number_ << "\".\n";
    this->number_ = static_number_;
  }
  virtual ~Observer()
  {
    cout << "Goodbye, i was the observer.\"" << this->number_ << "\".\n";
  }

  void PrintInfo()
  {
    cout << "Observer \"" << number_ << "\": a new message is available -> " << message_from_subject_ << endl;
  }
  void Update(const string &message_from_subject) override
  {
    message_from_subject_ = message_from_subject;
    PrintInfo();
  }
  void RemoveMeFromThisList()
  {
    subject_.Detach(this);
    cout << "Observer \"" << number_ << "\" removed from the list.\n";
  }
};

int Observer::static_number_ = 0;

void ClientCode()
{
  Subject *subject = new Subject;
  Observer *observer1 = new Observer(*subject);
  Observer *observer2 = new Observer(*subject);
  Observer *observer3 = new Observer(*subject);
  Observer *observer4;
  Observer *observer5;

  subject->CreateMessage("Hello world!");
  observer3->RemoveMeFromThisList();

  subject->CreateMessage("Weather not good ;(((");
  observer4 = new Observer(*subject);
  observer4->PrintInfo();

  observer2->RemoveMeFromThisList();
  observer5 = new Observer(*subject);

  subject->CreateMessage("New car is great!! ");
  observer5->RemoveMeFromThisList();

  observer4->RemoveMeFromThisList();
  observer1->RemoveMeFromThisList();

  delete observer1;
  delete observer2;
  delete observer3;
  delete observer4;
  delete observer5;

  delete subject;
}
int main()
{
  ClientCode();
  return 0;
}