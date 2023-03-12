// a lot of devs consider it as an antipattern, the usage in c++ is declined.
#include <iostream>
#include <string>
#include <thread>

using namespace std;

class Singleton
{
protected:
  string value_;
  static Singleton *singleton_;
  Singleton(const string value) : value_(value) {}

public:
  // singletons should not be cloneable
  Singleton(Singleton &other) = delete;
  // singtons should not be assignable
  void operator=(const Singleton &) = delete;

  static Singleton *GetInstance(const string &value);

  void someBusinessLogic()
  {
  }

  string getValue() const
  {
    return value_;
  }
};

Singleton *Singleton::singleton_ = nullptr;
// Static methods should be defined outsite of the class
Singleton *Singleton::GetInstance(const string &value)
{
  if (singleton_ == nullptr)
  {
    singleton_ = new Singleton(value);
  }
  return singleton_;
}

void ThreadFoo()
{
  this_thread::sleep_for(chrono::milliseconds(1000));
  Singleton *singleton = Singleton::GetInstance("Foo");

  cout << singleton->getValue() << endl;
}

void ThreadBar()
{
  this_thread::sleep_for(chrono::milliseconds(1000));
  Singleton *singleton = Singleton::GetInstance("Bar");

  cout << singleton->getValue() << endl;
}

void testModification()
{
  Singleton *initSingleton = Singleton::GetInstance("Init");
  cout << initSingleton->getValue() << endl;

  Singleton *copiedSingleton = initSingleton;
  cout << copiedSingleton->getValue() << endl;
}

int main()
{

  std::cout << "If you see the same value, then singleton was reused (yay!\n"
            << "If you see different values, then 2 singletons were created (booo!!)\n\n"
            << "RESULT:\n";

  thread t1(ThreadFoo);
  thread t2(ThreadBar);

  t1.join();
  t2.join();

  cout << "------\n";

  testModification();

  return 0;
}