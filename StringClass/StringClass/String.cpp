#include "String.h"
#include <iostream>

String::String()
{
    m_string = new char[1];
}

String::String(const char* _str)
{
    // I could use strcpy, but writing it from scratch is more fun, though probably less optimised

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

int String::Length() const
{
    // I could use strlen, but writing it from scratch is more fun, though probably less optimised

    int len = 0;
    // Loop through string and count length until null terminator is reached
    while (m_string[len] != '\0') {
        len++;
    }
    return len;
}

char& String::CharacterAt(int _index)
{
    // check if index is properly inside the bounds of the string
    if (_index < 0 || _index >= Length()) {
        return m_string[Length()]; // returns the null terminator at the end of the string
    }

    // Return the char at that index in the string
    return m_string[_index];
}

const char& String::CharacterAt(int _index) const
{
    // check if index is properly inside the bounds of the string
    if (_index < 0 || _index >= Length()) {
        return '\0';
    }

    // Return the char at that index in the string
    return m_string[_index];
}

bool String::EqualTo(const String& _other) const
{
    // Check if strings are same length first so there are no issues when looping through both later
    if (Length() != _other.Length()) {
        return false;
    }

    // Loop through each char and compare in both strings
    for (int i = 0; i < Length(); i++) {
        if (CStr()[i] != _other[i]) {
            // One char does not match, therefore the strings are not identical, so return false
            return false;
        }
    }
    // All characters in both strings are identical, therefore return true
    return true;
}

void String::Append(const String& _str)
{
    // Make new empty temp char pointer with the right size
    char* temp = new char[Length() + _str.Length() + 1];
    // Set it to the old string, then add the new string onto the end
    strcpy_s(temp, Length() + _str.Length() + 1, m_string);
    strcat_s(temp, Length() + _str.Length() + 1, _str.CStr());

    // Reallocate the memory
    delete[] m_string;
    m_string = new char[Length() + _str.Length() + 1];
    m_string = temp;
}

void String::Prepend(const String& _str)
{
    // Make new empty temp char pointer with the right size
    char* temp = new char[Length() + _str.Length() + 1];
    // Set it to the new string, then add the old string onto the end, effectively prepending the new string
    strcpy_s(temp, Length() + _str.Length() + 1, _str.CStr());
    strcat_s(temp, Length() + _str.Length() + 1, m_string);

    // Reallocate the memory
    delete[] m_string;
    m_string = new char[Length() + _str.Length() + 1];
    m_string = temp;
}

const String String::ToLower()
{
    // Make new dynamic char array with appropriate length
    char * temp = new char[Length() + 1];
    strcpy_s(temp, Length() + 1, m_string);

    // Loop through each char and check if it is uppercase using its ASCII value (65-90)
    for (int i = 0; i < Length(); i++) {
        if (temp[i] > 64 && temp[i] < 91) {
            // If uppercase, add 32 to the ASCII value to convert to lowercase
            temp[i] += 32;
        }
    }

    // Convert to String
    String tempString(temp);
    delete[] temp;
    return tempString;
}

const String String::ToUpper()
{
    // Make new dynamic char array with appropriate length
    char* temp = new char[Length() + 1];
    strcpy_s(temp, Length() + 1, m_string);

    // Loop through each char and check if it is lowercase using its ASCII value (97-122)
    for (int i = 0; i < Length(); i++) {
        if (temp[i] > 96 && temp[i] < 122) {
            // If lowercase, subtract 32 from the ASCII value to convert to uppercase
            temp[i] -= 32;
        }
    }

    // Convert to String
    String tempString(temp);
    delete[] temp;
    return tempString;
}

int String::Find(const String& _str)
{
    return Find(0, _str);
}

int String::Find(int _startIndex, const String& _str)
{
    // Check if find string is too long to be inside the search string
    if (_str.Length() > (Length() - _startIndex)) {
        return -1;
    }

    // Loop through each possible position for the substring, starting from the specified index
    for (int searchIndex = _startIndex; searchIndex < Length() - _str.Length() + 1; searchIndex++) {
        bool found = true;
        // Loop through the substring and check each char to see if it matches
        for (int substringIndex = 0; substringIndex < _str.Length(); substringIndex++) {
            if (m_string[searchIndex + substringIndex] != _str[substringIndex]) {
                found = false;
                break;
            }
        }

        if (found) {
            return searchIndex;
        }
    }

    // If func reaches this point, then there were no matches found, so return -1
    return -1;
}

String String::Substring(int _startIndex, int _endIndex)
{
    // check that indices are inside the bounds
    if (_startIndex < 0 || _endIndex > Length()) {
        std::cout << "Substring error: out of bounds index!";
        return String("");
    }

    if (_startIndex > _endIndex) {
        std::cout << "Substring error: start index greater than end index!";
        return String("");
    }

    // create temp array to store the substring
    char * temp = new char[_endIndex - _startIndex + 1];

    // set each char of temp
    for (int i = _startIndex; i < _endIndex; i++) {
        temp[i - _startIndex] = m_string[i];
    }
    temp[_endIndex - _startIndex] = '\0';

    return String(temp);
}

void String::Replace(const String& _find, const String& _replace)
{
    bool stillInstancesLeft = false;
    // Check for an instance of the find string
    int foundIndex = Find(_find);
    stillInstancesLeft = (foundIndex != -1); // keep finding and replacing while the target string remains inside this string
    while (stillInstancesLeft){
        // temp string becomes (start portion of OG string up to found substring) + (replace string) + (end portion of OG string)
        String temp = Substring(0, foundIndex);
        temp += _replace;
        temp += Substring(foundIndex + _find.Length(), Length());

        // Reallocate memory 
        delete[] m_string;
        m_string = new char[temp.Length() + 1];
        strcpy_s(m_string, temp.Length() + 1, temp.CStr());

        // Check for more instances of the find string
        foundIndex = Find(_find);
        stillInstancesLeft = (foundIndex != -1); // keep finding and replacing while the target string remains inside this string
    }
}

void String::ReadFromConsole()
{
    // Reallocate memory and get line of input
    delete[] m_string;
    m_string = new char[10000];
    std::cin.getline(m_string, 10000);
}

void String::WriteToConsole()
{
    std::cout << m_string;
}

const char* String::CStr() const
{
	return m_string;
}


void String::operator = (const String& other)
{
    // This is just the same code as the copy constructor above
    m_string = new char[other.Length() + 1];

    // Loop through each char in the input string and assign it to the new string
    for (int i = 0; i < other.Length(); i++) {
        m_string[i] = other.CStr()[i];
    }

    // Add null terminator to the end of the string
    m_string[other.Length()] = '\0';
}

bool String::operator == (const String& other)
{
    return EqualTo(other);
}

bool String::operator != (const String& other)
{
    return EqualTo(other) == false;
}

bool String::operator < (const String& other)
{
    // I could use strcmp, but writing it from scratch is more fun, though probably less optimised

    if (EqualTo(other)) return false;

    for (int i = 0; i < Length(); i++) {
        if (other[i] == '\n') {
            // other string is shorter than this one, therefore it goes before this string in the alphabet
            return false;
        }

        if (m_string[i] < other[i]) {
            return true;
        }
        else if (m_string[i] > other[i]) {
            return false;
        }
        // otherwise the two letters are the same and so we move on to the next letter of both strings
    }

    // this string must be shorter than the other string, therefore it goes before the other string in the alphabet
    return true;
}

bool String::operator > (const String& other)
{
    return (*this < other == false);

}

char& String::operator [] (int _index)
{
    // check if magnitude of index is too big for the size of the string
    if (_index >= Length() || -_index >= Length()) {
        std::cout << "Out of bounds array index when attempting to access the string: '" << m_string << "' at index " << _index;
        exit(0);
    }
    
    // negative indexes start from the end of the string
    if (_index < 0) {
        return m_string[Length() + _index];
    }
    else {
        return m_string[_index];
    }
    
}

const char& String::operator [] (int _index) const
{
    // check if magnitude of index is too big for the size of the string
    if (_index >= Length() || -_index >= Length()) {
        std::cout << "Out of bounds array index when attempting to access the string: '" << m_string << "' at index " << _index;
        exit(0);
    }

    // negative indexes start from the end of the string
    if (_index < 0) {
        return m_string[Length() + _index];
    }
    else {
        return m_string[_index];
    }
}

const String String::operator + (const String& other) const
{
    String temp(m_string);
    temp.Append(other);
    return temp;
}

void String::operator += (const String& other)
{
    Append(other);
}


