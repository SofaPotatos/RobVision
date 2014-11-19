#pragma once

#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>

using namespace std;

/// sbsCStringOperator Class
///
/// This class works with string amendment.
class sbsCStringOperator
{
    public:
		/// A constructor.
		///
		/// This constructor creates an object to work with string.
        sbsCStringOperator();

		/// A destructor.
		///
		/// This destructor free the resources that the object may have.
        ~sbsCStringOperator();

    public:
		/// This member return the string in between 2 sub string.
		///
		///@param orgStr: The original string
		///@param startstr: The string that indicates the start of the string in between
		///@param endstr: The string that indicates the end of the string in between
		///@return amended string
        static string stringBetween(string orgStr, string startstr, string endstr);

		/// This member finds the sub string from the original string and return its index.
		///
		///@param orgStr: The original string
		///@param str: The sub string
		///@return index of the string, -1 if not found
    	static int findString(string orgStr, string str);

		/// This member return the string before the sub string.
		///
		///@param orgStr: The original string
		///@param str: The sub string
		///@return amended string
        static string stringBefore(string orgStr, string str);

		/// This member return the string after the sub string.
		///
		///@param orgStr: The original string
		///@param str: The sub string
		///@return amended string
        static string stringAfter(string orgStr, string str);

		/// This member trim the string with the sub string.
		///
		///@param orgStr: The original string
		///@param str: The sub string
		///@return vector which contain the trimmed string
        static vector<string> stringTrimming(string str, string sep);

		/// This member takes in a string and convert it into a double.
		///
		///@param v: The string to be convert
		///@return double value
        static double stringToDouble(string v);
};
