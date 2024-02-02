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

	// Returns length of string
	int Length() const;

	// Returns the character at the given index in the string
	char& CharacterAt(int _index);
	const char& CharacterAt(int _index) const;

	// Returns true if both strings are identical, otherwise returns false
	bool EqualTo(const String& _other) const;

	// Adds the provided string onto the end of this string
	String& Append(const String& _str);
	// Adds the provided string before the start of this string
	String& Prepend(const String& _str);

	// Converts all letters in string to lowercase
	void ToLower();
	// Converts all letters in string to uppercase
	void ToUpper();

	// Finds the specified substring, returns -1 if not present
	int Find(const String& _str);
	// Finds the specified substring from the start index, returns -1 if not present
	int Find(int _startIndex, const String& _str);

	// Find the specified substring and replaces it with a string
	String& Replace(const String& _find, const String& _replace);
	
	// Reads a line from console and saves the result to this string
	String& ReadFromConsole();
	// Writes this string to console
	String& WriteToConsole();

	// Returns a char pointer of the string stored in this object
	const char * CStr() const;

private:
	char * m_string;




};

