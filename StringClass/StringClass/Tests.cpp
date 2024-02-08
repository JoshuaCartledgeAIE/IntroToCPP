
#include <iostream>
#include "String.h"
using namespace std;

void HelloWorld();
void RunTests();


int main()
{
    HelloWorld();

    RunTests();
}


void HelloWorld() {
    // For Assessment Task 1
    // This is the most obfuscated hello world program lol
    // Eventually prints "Hello, World!" by using several functions of this String class

    String part1("Hi");
    String part2("OrLD!");
    String extraStuff("Take, the W to win");

    part1.Replace("i", "ello"); // part1 is now "Hello"
    part2.ToLower(); // part2 now says "orld!"

    String middle = extraStuff.Substring(4, 7); // middle is now ", t"
    middle[2] = extraStuff.CharacterAt(10); // middle is now ", W"

    part2.Prepend(middle); // part2 is now ", World!"
    String finalResult = part1 + part2; // Combine both parts
    finalResult.WriteToConsole(); // Print out the final "Hello, World!"
}

void RunTests() {
    // For Assessment Task 2:
    // Runs many different test cases to test each function of the string class

    // Testing constructors and CStr to print to console
    String test("one");
    String test2("two");
    String test3("three");
    String test4(test2);
    cout << "test: " << test << endl;
    cout << "test2: " << test2 << endl;
    cout << "test3: " << test3 << endl;
    cout << "test4: " << test4 << endl;
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
    cout << "Append test2 onto test: " << test << endl;
    test2.Prepend(test3);
    cout << "Prepend test3 onto test2: " << test2 << endl;
    test3 += test3;
    cout << "Append test3 onto itself: " << test3 << endl;
    cout << endl;

    // Testing ToUpper and ToLower
    String test5("!1!CaPiTaLisATIon!2!");
    cout << "test5: " << test5 << endl;
    test5.ToUpper();
    cout << "test5 in uppercase: " << test5 << endl;
    test5.ToLower();
    cout << "test5 in lowercase: " << test5 << endl;
    cout << endl;

    // Testing CharacterAt and the '[]' operator
    String test6("searchandyouwillfind");
    cout << "test6: " << test6 << endl;
    cout << "Character at index 4 in test6: " << test6.CharacterAt(4) << endl;
    cout << "Character at index 30 in test6: ";
    if (test6.CharacterAt(30) == '\0') {
        cout << "\\0 (error from out of bounds index)" << endl;
    }
    else {
        cout << test6.CharacterAt(30) << endl;
    }
    cout << "Character at index -2 in test6: " << test6[-2] << endl;

    // Testing Find
    cout << "Position of 'and' in test6: " << test6.Find("and") << endl;
    cout << "Position of 'a' in test6: " << test6.Find("a") << endl;
    cout << "Position of 'a' in test6 starting from index 4: " << test6.Find(4, "a") << endl;

    // Testing Substring (on seperate lines here since I know they will display error messages)
    cout << "Substring of test6 from 2 to 6: ";
    cout << test6.Substring(2, 6) << endl;
    cout << "Substring of test6 from 10 to 30: ";
    cout << test6.Substring(10, 30) << endl;
    cout << "Substring of test6 from 7 to 5: ";
    cout << test6.Substring(7, 5) << endl;
    cout << endl;

    // Testing Replace
    String test7("I like eating lots and lots of food");
    cout << "test7: " << test7 << endl;
    test7.Replace("lots", "oodles");
    cout << "Replace 'lots' with 'oodles' in test7: " << test7 << endl;
    cout << endl;

    // Testing '<' and '>' operator
    String test8("child");
    String test9("chores");
    String test10("children");
    cout << "test8: " << test8 << endl;
    cout << "test9: " << test9 << endl;
    cout << "test10: " << test10 << endl;
    cout << "test8 < test9: " << (test8 < test9) << endl;
    cout << "test8 > test9: " << (test8 > test9) << endl;
    cout << "test9 < test10: " << (test9 < test10) << endl;
    cout << "test8 < test10: " << (test8 < test10) << endl;
    cout << endl;

    // Testing ReadFromConsole and WriteToConsole
    String testinput("");
    cout << "Enter a string or phrase (this will be repeated back to you): ";
    testinput.ReadFromConsole();
    cout << "You entered: ";
    testinput.WriteToConsole();
}

