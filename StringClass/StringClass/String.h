#pragma once
class String
{
public:
	// Constructor and destructor methods
	String();
	String(const char* _str);
	String(const String& _other);
	~String();

		// String Utility Methods

	// Returns length of string
	int Length() const;

	// Returns the character at the given index in the string
	char& CharacterAt(int _index);
	const char& CharacterAt(int _index) const;

	// Returns true if both strings are identical, otherwise returns false
	bool EqualTo(const String& _other) const;

	// Adds the provided string onto the end of this string
	void Append(const String& _str);
	// Adds the provided string before the start of this string
	void Prepend(const String& _str);

	// Converts all letters in string to lowercase
	void ToLower();
	// Converts all letters in string to uppercase
	void ToUpper();

	// Finds the specified substring, returns -1 if not present
	int Find(const String& _str);
	// Finds the specified substring from the start index, returns -1 if not present
	int Find(int _startIndex, const String& _str);

	// Returns a substring of the original string starting at startIndex (inclusive) and ending before endIndex (exclusive)
	String Substring(int _startIndex, int _endIndex);

	// Find the specified substring and replaces it with a string
	void Replace(const String& _find, const String& _replace);
	
	// Reads a line from console and saves the result to this string
	void ReadFromConsole();
	// Writes this string to console
	void WriteToConsole();

	// Returns a char pointer of the string stored in this object
	const char * CStr() const;

		// Operators

	// Assign lhs to rhs

	void operator = (const String& other);

	// Check if one string is identical to another
	bool operator == (const String& other);
	// Check if one string is not identical to another
	bool operator != (const String& other);
	// Check if one string comes before another in the alphabet
	bool operator < (const String& other);
	// Check if one string comes after another in the alphabet
	bool operator > (const String& other);

	// Access the character at the given index in the string
	char& operator [] (int _index);
	const char& operator [] (int _index) const;

	// Concatenate two strings onto each other and return the result
	const String operator + (const String& other) const;
	// Concatenate the string onto this string, modifying this original string
	void operator += (const String& other);

	// Implicit conversion to char* (for cout purposes)
	operator char* () { return m_string; };
	

private:
	// The char pointer to the char array (string) that this object holds
	char * m_string;




};

