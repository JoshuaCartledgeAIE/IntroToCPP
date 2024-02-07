
#include <iostream>
#include "String.h"
using namespace std;

int main()
{
    // Test cases:
    String test("one");
    String test2("two");
    String test3("three");
    String test4(test2);
    cout << "test: " << test.CStr() << endl;
    cout << "test2: " << test2.CStr() << endl;
    cout << "test3: " << test3.CStr() << endl;
    cout << "test4: " << test4.CStr() << endl;
    cout << endl;

    // Testing EqualTo
    cout << "Is test1 equal to test2? " << test.EqualTo(test2) << endl;
    cout << "Is test2 equal to test4? " << test2.EqualTo(test4) << endl;
    cout << endl;

    // Testing Append and Prepend
    test.Append(test2);
    cout << "Append test2 onto test: " << test.CStr() << endl;
    test2.Prepend(test3);
    cout << "Prepend test3 onto test2: " << test2.CStr() << endl;
    test3.Append(test3);
    cout << "Append test3 onto itself: " << test3.CStr() << endl;
    cout << endl;

    // Testing ToUpper and ToLower
    String test5("!1!CaPiTaLisATIon!2!");
    cout << "test5: " << test5.CStr() << endl;
    test5.ToUpper();
    cout << "test5 in uppercase: " << test5.CStr() << endl;
    test5.ToLower();
    cout << "test5 in lowercase: " << test5.CStr() << endl;
    cout << endl;

    // Testing CharacterAt and Find
    String test6("searchandyouwillfind");
    cout << "test6: " << test6.CStr() << endl;
    cout << "Character at index 4 in test6: " << test6.CharacterAt(4) << endl;
    cout << "Position of 'and' in test6: " << test6.Find(String("and")) << endl;
    cout << "Position of 'a' in test6: " << test6.Find(String("a")) << endl;
    cout << "Position of 'a' in test6 starting from index 4: " << test6.Find(4, String("a")) << endl;
    
}

