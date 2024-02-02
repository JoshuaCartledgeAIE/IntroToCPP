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

//char& String::CharacterAt(int _index)
//{
//    // TODO: insert return statement here
//}
//
//const char& String::CharacterAt(int _index) const
//{
//    // TODO: insert return statement here
//}

bool String::EqualTo(const String& _other) const
{
    // Check if strings are same length first so there are no issues when looping through both later
    if (Length() != _other.Length()) {
        return false;
    }

    // Loop through each char and compare in both strings
    for (int i = 0; i < Length(); i++) {
        if (CStr()[i] != _other.CStr()[i]) {
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

void String::Replace(const String& _find, const String& _replace)
{

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


