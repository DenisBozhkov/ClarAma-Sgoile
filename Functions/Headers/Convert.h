#ifndef CONVERT_H
#define CONVERT_H

#include "config.h"

namespace Functions
{
	package Convert
	{
		static wstring ToWString(string str)
		{
			return wstring_convert<codecvt_utf8<wchar_t>>().from_bytes(str);
		}
		static string ToString(wstring str)
		{
			return wstring_convert<codecvt_utf8<wchar_t>>().to_bytes(str);
		}
		static string ToString(int i)
		{
			return to_string(i);
		}
		static string ToString(double i)
		{
			return to_string(i);
		}
		static int ToInt(string str)
		{
			return stoi(str.c_str());
		}
		static double ToDouble(string str)
		{
			return stod(str.c_str());
		}
		template<class EnumType> static EnumType ToEnum(string str)
		{
			return (EnumType)ToInt(str);
		}
	};
}

#endif