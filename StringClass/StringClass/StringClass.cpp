
#include <iostream>
#include "String.h"
using namespace std;

int main()
{
    // Test cases:
    String name("one");
    String name2("two");
    String name3("three");
    String name4(name2);
    cout << "name: " << name.CStr() << endl;
    cout << "name2: " << name2.CStr() << endl;
    cout << "name3: " << name3.CStr() << endl;
    cout << "name4: " << name4.CStr() << endl;

    cout << "Is name 1 equal to name 2? " << name.EqualTo(name2) << endl;
    cout << "Is name 2 equal to name 4? " << name2.EqualTo(name4) << endl;

    name.Append(name2);
    cout << "Append name2 onto name: " << name.CStr() << endl;
    name2.Prepend(name3);
    cout << "Prepend name3 onto name2: " << name2.CStr() << endl;
    name3.Append(name3);
    cout << "Append name3 onto itself: " << name3.CStr() << endl;
    
}

