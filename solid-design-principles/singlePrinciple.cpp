// a class should have a single reason to change
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

struct Journal
{
    string title;
    vector<string> entries;
    Journal(const string &title) : title(title) {}
    void add_entry(const string &entry)
    {
        // Static variables in a Function: When a variable is declared as static,
        // space for it gets allocated for the lifetime of the program.
        // Even if the function is called multiple times, space for the static variable
        // is allocated only once and the value of variable in the previous call gets
        // carried through the next function call.
        static int count = 1;
        entries.push_back(lexical_cast<string>(count++) + ": " + entry);
        cout << count << endl;
    }
};

int main()
{
    Journal journal("dear diary");
    journal.add_entry("i ate a bug");
    journal.add_entry("i cried");
    journal.add_entry("i felt sad");
    for (string line : journal.entries)
    {
        cout << line << endl;
    }
    return 0;
}