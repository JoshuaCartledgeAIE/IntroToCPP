#include "String.h"

String::String()
{

}

String::String(const char* _str)
{

}

String::String(const String& _other)
{
}

String::~String()
{
	delete[] m_string;
}

int String::Length() const
{
	return 0;
}

void String::ToLower()
{
}

void String::ToUpper()
{
}

int String::Find()
{
	return 0;
}

char* String::CStr()
{
	return m_string;
}


