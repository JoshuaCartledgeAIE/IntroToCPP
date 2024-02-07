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

void String::ToLower()
{
    // Loop through each char and check if it is uppercase using its ASCII value (65-90)
    for (int i = 0; i < Length(); i++) {
        if (m_string[i] > 64 && m_string[i] < 91) {
            // If uppercase, add 32 to the ASCII value to convert to lowercase
            m_string[i] += 32;
        }
    }
}

void String::ToUpper()
{
    // Loop through each char and check if it is lowercase using its ASCII value (97-122)
    for (int i = 0; i < Length(); i++) {
        if (m_string[i] > 96 && m_string[i] < 122) {
            // If lowercase, subtract 32 from the ASCII value to convert to uppercase
            m_string[i] -= 32;
        }
    }
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
    for (int searchIndex = _startIndex; searchIndex < Length() - _str.Length(); searchIndex++) {
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

void String::Replace(const String& _find, const String& _replace)
{
    bool stillInstancesLeft = false;
    while (stillInstancesLeft){
        int foundIndex = Find(_find);
        stillInstancesLeft = (foundIndex != -1); // keep finding and replacing while the target string remains inside this string
    }

}

void String::ReadFromConsole()
{
    std::cin.getline(m_string, 150);
}

void String::WriteToConsole()
{
    std::cout << m_string;
}

const char* String::CStr() const
{
	return m_string;
}


bool String::operator == (String& other)
{
    return EqualTo(other);
}

bool String::operator != (String& other)
{
    return EqualTo(other) == false;
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

String String::operator + (String& other)
{
    String temp(m_string);
    temp.Append(other);
    return temp;
}

void String::operator += (String& other)
{
    Append(other);
}


