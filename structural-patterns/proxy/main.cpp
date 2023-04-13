#include <algorithm>
#include <iostream>
#include <list>
#include <string>

using namespace std;

class Subject
{
public:
  virtual void Request() const = 0;
};

class RealSubject : public Subject
{
public:
  void Request() const override
  {
    cout << "Real subject: handling request.\n";
  }
};

class Proxy : public Subject
{
private:
  RealSubject *real_subject_;

  bool CheckAccess() const
  {
    cout << "Proxy: checking access prior to firing a real request.\n";
    return true;
  }

  void LogAccess() const
  {
    cout << "Proxy: Logging the time of request.\n";
  }

public:
  // copy constructor
  Proxy(RealSubject *real_subject) : real_subject_(new RealSubject(*real_subject)) {}
  ~Proxy() { delete real_subject_; }

  void Request() const override
  {
    if (this->CheckAccess())
    {
      this->real_subject_->Request();
      this->LogAccess();
    }
  }
};

void ClientCode(const Subject &subject)
{
  subject.Request();
}

int main()
{
  cout << "Client: execute with real subject.\n";
  RealSubject *real_subject = new RealSubject;
  ClientCode(*real_subject);

  cout << endl;

  cout << "Client: execute with proxy.\n";
  Proxy *proxy = new Proxy(real_subject);
  ClientCode(*proxy);

  delete real_subject;
  delete proxy;

  return 0;
}
