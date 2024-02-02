#pragma once
class String
{
public:
	// Constructor and destructor methods
	String();
	String(const char* _str);
	String(const String& _other);
	~String();

public:
	// String Utility Methods
	int Length() const;

	void ToLower();
	void ToUpper();

	int Find();

	char * CStr();

private:
	char * m_string;




};

