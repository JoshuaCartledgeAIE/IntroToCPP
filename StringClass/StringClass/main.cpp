
#include <iostream>
#include "String.h"
using namespace std;

int main()
{
    // Test cases:

    // Testing constructors and CStr to print to console
    String test("one");
    String test2("two");
    String test3("three");
    String test4(test2);
    cout << "test: " << test.CStr() << endl;
    cout << "test2: " << test2.CStr() << endl;
    cout << "test3: " << test3.CStr() << endl;
    cout << "test4: " << test4.CStr() << endl;
    cout << endl;

    // Testing Length
    cout << "Length of test3: " << test3.Length() << endl << endl;

    // Testing '+' operator
    cout << "test + test2 + test3 + test: " << (test + test2 + test3 + test).CStr() << endl << endl;

    // Testing EqualTo and '==' operator
    cout << "Is test1 equal to test2? " << test.EqualTo(test2) << endl;
    cout << "Is test2 equal to test4? " << (test2 == test4) << endl;
    cout << endl;

    // Testing Append and Prepend and the '+=' operator
    test.Append(test2);
    cout << "Append test2 onto test: " << test.CStr() << endl;
    test2.Prepend(test3);
    cout << "Prepend test3 onto test2: " << test2.CStr() << endl;
    test3 += test3;
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

    // Testing CharacterAt, the '[]' operator, Find and Substring
    String test6("searchandyouwillfind");
    cout << "test6: " << test6.CStr() << endl;
    cout << "Character at index 4 in test6: " << test6.CharacterAt(4) << endl;
    cout << "Character at index -2 in test6: " << test6[-2] << endl;

    cout << "Position of 'and' in test6: " << test6.Find(String("and")) << endl;
    cout << "Position of 'a' in test6: " << test6.Find(String("a")) << endl;
    cout << "Position of 'a' in test6 starting from index 4: " << test6.Find(4, String("a")) << endl;

    cout << "Substring of test6 from 2 to 6: " << test6.Substring(2, 6).CStr() << endl;
    cout << endl;

    // Testing Replace
    String test7("I like eating lots and lots of food");
    cout << "test7: " << test7.CStr() << endl;
    test7.Replace(String("lots"), String("oodles"));
    cout << "Replace 'lots' with 'oodles' in test7: " << test7.CStr() << endl;
    cout << endl;

    // Testing '<' and '>' operator
    String test8("child");
    String test9("chores");
    String test10("children");
    cout << "test8: " << test8.CStr() << endl;
    cout << "test9: " << test9.CStr() << endl;
    cout << "test10: " << test10.CStr() << endl;
    cout << "test8 < test9: " << (test8 < test9) << endl;
    cout << "test8 > test9: " << (test8 > test9) << endl;
    cout << "test9 < test10: " << (test9 < test10) << endl;
    cout << "test8 < test10: " << (test8 < test10) << endl;
    cout << endl;

    // Testing ReadFromConsole and WriteToConsole
    String testinput("");
    cout << "Enter a string (this will be repeated back to you): ";
    testinput.ReadFromConsole();
    cout << "You entered: ";
    testinput.WriteToConsole();
}

