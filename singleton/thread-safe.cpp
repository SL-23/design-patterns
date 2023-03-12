#include <iostream>
#include <string>
#include <thread>

using namespace std;

// 1. make the default constructor private
// to prevent other objects from using the new operator
// with the Singleton class
// 2. create a static creation method that acts as a constructor.
// under the hood, this method calls the private constructor
// to create an object and saves it in a static field.
// All following calls to this method return the cached object.

// if your code has access to the Singleton class, then it's able to
// call the Singleton's static method.
// ! whenever the method is called, the SAME object is always returned.
class Singleton
{
private:
  static Singleton *pinstance_;
  // the mutex class is a synchronisation primitive that
  // can be used to protect shared data from being simultaneously
  // accessed by multiple threads.s
  static mutex mutex_;

protected:
  Singleton(const string value) : value_(value) {}
  ~Singleton() {}

  string value_;

public:
  Singleton(Singleton &other) = delete;

  void operator=(const Singleton &) = delete;

  static Singleton *GetInstance(const string &value);

  void someBusinessLogic() {}

  string getValue() const
  {
    return value_;
  }
};
// define static methods outside of the class
Singleton *Singleton::pinstance_ = nullptr;
mutex Singleton::mutex_;

Singleton *Singleton::GetInstance(const string &value)
{
  lock_guard<mutex> lock(mutex_);
  if (pinstance_ == nullptr)
  {
    pinstance_ = new Singleton(value);
  }
  return pinstance_;
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