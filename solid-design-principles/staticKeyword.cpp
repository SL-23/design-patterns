#include <iostream>
#include <string>

using namespace std;
/********************* in function *********************/
void demo()
{
  static int count = 0;
  cout << count << " ";
  count++;
}
/********************* in class *********************/
class ErrorStatic
{
public:
  /*
  As the variables declared as static are initialized only once
  as they are allocated space in separate static storage so,
  the static variables in a class are shared by the objects.
  There can not be multiple copies of same static variables for different objects.
  */
  static int errorVar;

  /* a static variable inside a class should be initialized explicitly by the user
  using the class name and scope resolution operator outside the class as shown below
  */
  static int correctVar;

  ErrorStatic()
  {
  }
};

/** Init outside using class name and scope resolution operation outside the class **/
int ErrorStatic::correctVar = 10;

/********************* Static Members of Class *********************/
class MyClass
{
  int i;
  string objName;

public:
  MyClass(string objName_)
  {
    i = 0;
    cout << "Constructor for " << objName_ << endl;
    objName = objName_;
  }
  ~MyClass()
  {
    cout << "Destructor\n";
  }
};

int main()
{
  for (int i = 0; i < 5; ++i)
  {
    demo();
    // ---> prints out 0,1,2,3,4

    /*
    Static variables in a Function:
    When a variable is declared as static,
    space for it gets allocated for the
    lifetime of the program.
    Even if the function is called multiple times,
    space for the static variable is allocated only once
    and the value of variable in the previous call
    gets carried through the next function call.
    */
  }

  /** static variables CANNOT be initialized using constructors. **/
  // ErrorStatic errStatic1;
  // errStatic1.errorVar = 2;
  // ErrorStatic errStatic2;
  // errStatic2.errorVar = 3;

  ErrorStatic initOutside;
  cout << "init outside class " << initOutside.correctVar << " is successful!" << endl;

  int x = 0;
  if (x == 0)
  {
    /*
    soon as the control of if block gets over the destructor
    is invoked as the scope of object is inside the if block
    only where it is declared.
    */
    MyClass obj1("NOOOO static object");
    // -->
    // Constructor for NOOOO static object
    // Destructor
    // Out of block
  }

  cout << "Out of block" << endl;

  if (x == 0)
  {
    // Now the destructor is invoked after the end of main.
    // This happened because the scope of static object is
    // through out the life time of program.
    static MyClass obj2("STATIC object");
    // -->
    //   Constructor for STATIC object
    // Out of block
    // Destructor
  }

  cout << "Out of block" << endl;

  return 0;
}