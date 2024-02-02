#include "String.h"
#include <iostream>

String::String()
{
    m_string = new char[0];
}

String::String(const char* _str)
{
    // I could use strcpy, but this is cooler
    m_string = new char[strlen(_str) + 1];

    // Loop through each char in the input string and assign it to the new string
    for (int i = 0; i < strlen(_str); i++) {
        m_string[i] = _str[i];
    }

    // Add null terminator to the end of the string
    m_string[strlen(_str)] = '\0';
}

String::String(const String& _other)
{
    m_string = new char[_other.Length() + 1];

    // Loop through each char in the input string and assign it to the new string
    for (int i = 0; i < _other.Length(); i++) {
        m_string[i] = _other.CStr()[i];
    }

    // Add null terminator to the end of the string
    m_string[_other.Length()] = '\0';
}

String::~String()
{
	delete[] m_string;
}

// Returns length of string
int String::Length() const
{
    int len = 0;
    // Loop through string and count length until null terminator is reached
    while (m_string[len] != '\0') {
        len++;
    }
    return len;
}

char& String::CharacterAt(int _index)
{
    // TODO: insert return statement here
}

const char& String::CharacterAt(int _index) const
{
    // TODO: insert return statement here
}

bool String::EqualTo(const String& _other) const
{
    return false;
}

String& String::Append(const String& _str)
{
    // TODO: insert return statement here
}

String& String::Prepend(const String& _str)
{
    // TODO: insert return statement here
}

void String::ToLower()
{
}

void String::ToUpper()
{
}

int String::Find(const String& _str)
{
    return 0;
}

int String::Find(int _startIndex, const String& _str)
{
    return 0;
}

String& String::Replace(const String& _find, const String& _replace)
{
    // TODO: insert return statement here
}

String& String::ReadFromConsole()
{
    // TODO: insert return statement here
}

String& String::WriteToConsole()
{
    // TODO: insert return statement here
}

const char* String::CStr() const
{
	return m_string;
}


bool CompareStrings(const char stringA[], const char stringB[]) {
    // Returns true if both strings are identical, otherwise returns false
    // Check if strings are same length first so there are no issues when looping through both later
    if (GetLength(stringA) != GetLength(stringB)) {
        return false;
    }

    // Loop through each char and compare in both strings
    for (int i = 0; i < GetLength(stringA); i++) {
        if (stringA[i] != stringB[i]) {
            // One char does not match, therefore the strings are not identical, so return false
            return false;
        }
    }
    // All characters in both strings are identical, therefore return true
    return true;
}



char* ConcatStrings(const char stringA[], const char stringB[]) {
    // Make a new dynamic array based on the combined length of both inputted strings
    char* newString = new char[GetLength(stringA) + GetLength(stringB) + 1];

    // Loop through each char in the first string and assign it to the new string
    for (int i = 0; i < GetLength(stringA); i++) {
        newString[i] = stringA[i];
    }
    // Loop through each char in the second string and assign it to the new string
    for (int i = 0; i < GetLength(stringB); i++) {
        newString[i + GetLength(stringA)] = stringB[i];
    }

    // Add null terminator to the end of the string and return the finished concatenated string
    newString[GetLength(stringA) + GetLength(stringB)] = '\0';
    return newString;
}

int main()
{
    char string1[] = "test";
    std::cout << string1 << std::endl;
    char string2[] = "combo";
    std::cout << string2 << std::endl;

    char* string3 = ConcatStrings(string1, string2);

    std::cout << string3 << std::endl;

    delete[] string3;
}


