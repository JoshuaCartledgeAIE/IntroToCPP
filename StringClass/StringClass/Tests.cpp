
#include <iostream>
#include "String.h"
#include <fstream>
using namespace std;

void RunTests();


int main()
{
    RunTests();
    system("pause");
}

void RunTests() {
    // For Assessment Task 3:
    // Runs many different test cases to test each function of the string class, and prints results to a file

    // Array to log test successes
    bool successes[13];
    int testCount = 0;

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
    cout << "Length of test3 (expected result: 5): " << test3.Length() << endl << endl;
    successes[testCount] = (test3.Length() == 5);
    testCount++;

    // Testing '+' operator
    cout << "test + test2 + test3 + test (expected result: onetwothreeone): " << (test + test2 + test3 + test).CStr() << endl << endl;
    successes[testCount] = (String("onetwothreeone") == (test + test2 + test3 + test));
    testCount++;

    // Testing EqualTo and '==' operator

    cout << "Is test2 equal to test4 (expected result: 1)? " << (test2 == test4) << endl;
    successes[testCount] = ((test2 == test4) == 1);
    testCount++;
    cout << endl;

    // Testing Append and Prepend
    test.Append(test2);
    cout << "Append test2 onto test (expected result: onetwo): " << test << endl;
    successes[testCount] = (test == "onetwo");
    testCount++;
    test2.Prepend(test3);
    cout << "Prepend test3 onto test2 (expected result: threetwo): " << test2 << endl;
    successes[testCount] = (test2 == "threetwo");
    testCount++;
    cout << endl;

    // Testing ToUpper and ToLower
    String test5("!1!CaPiTaLisATIon!2!");
    cout << "test5: " << test5 << endl;
    cout << "test5 in uppercase (expected result: !1!CAPITALISATION!2!): " << test5.ToUpper().CStr() << endl;
    successes[testCount] = (String("!1!CAPITALISATION!2!") == test5.ToUpper());
    testCount++;
    cout << "test5 in lowercase (expected result: !1!capitalisation!2!): " << test5.ToLower().CStr() << endl;
    successes[testCount] = (String("!1!capitalisation!2!") == test5.ToLower());
    testCount++;
    cout << endl;

    // Testing CharacterAt and the '[]' operator
    String test6("searchandyouwillfind");
    cout << "test6: " << test6 << endl;
    cout << "Character at index 4 in test6 (expected result: c): " << test6.CharacterAt(4) << endl;
    successes[testCount] = (test6.CharacterAt(4) == 'c');
    testCount++;
    cout << "Character at index -2 in test6 (expected result: n): " << test6[-2] << endl << endl;
    successes[testCount] = (test6[-2] == 'n');
    testCount++;

    // Testing Find
    cout << "Position of 'and' in test6 (expected result: 6): " << test6.Find("and") << endl;
    successes[testCount] = (test6.Find("and") == 6);
    testCount++;

    // Testing Substring
    cout << "Substring of test6 from 2 to 6 (expected result: arch): " << test6.Substring(2, 6) << endl;
    successes[testCount] = (test6.Substring(2, 6) == "arch");
    testCount++;


    // Testing Replace
    String test7("lots and lots of food");
    cout << "test7: " << test7 << endl;
    test7.Replace("lots", "oodles");
    cout << "Replace 'lots' with 'oodles' in test7 (expected result: oodles and oodles of food): " << test7 << endl;
    successes[testCount] = (test7 == "oodles and oodles of food");
    testCount++;
    cout << endl;

    // Testing '<' operator
    String test8("child");
    String test9("chores");
    cout << "test8: " << test8 << endl;
    cout << "test9: " << test9 << endl;
    cout << "test8 < test9 (expected result: 1): " << (test8 < test9) << endl;
    successes[testCount] = ((test8 < test9) == 1);
    testCount++;
    cout << endl;

    // Calculate success percentage of all test cases
    float successPercent = 0;
    for (int i : successes) {
        successPercent += i;
    }
    successPercent /= 13;

    // get current time and date
    struct tm newtime;
    time_t now = time(0);
    localtime_s(&newtime, &now);
    int sec = newtime.tm_sec;
    int min = newtime.tm_min;
    int hr = newtime.tm_hour;
    int day = newtime.tm_mday;
    int mon = 1 + newtime.tm_mon;
    int yr = 1900 + newtime.tm_year;


    // Open text file
    fstream file;
    file.open("testlog.txt", ios::out);

    const char* testNames[13] = { "Length", "+ Operator", "EqualTo and == Operator", "Append", "Prepend", "ToUpper", "ToLower", "CharacterAt", "[] Operator", "Find", "Substring", "Replace", "< Operator"};

    // Log date and success percentage at top of file
    file << "Date: " << day << "/" << mon << "/" << yr << " Time: " << hr << ":" << min << ":" << sec << " Successful " << successPercent * 100 << "%" << endl;
    // For each test, log the name of the test and the result into the text file
    for (int i = 0; i < 13; i++) {
        file << "Test " << i << " " << testNames[i] << " " << (successes[i] ? "Successful" : "Failed") << endl;
    }

    // Close text file
    file.close();
}

