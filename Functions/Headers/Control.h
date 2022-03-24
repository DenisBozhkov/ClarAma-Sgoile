#ifndef CONTROL_H
#define CONTROL_H

#include "config.h"

namespace Functions
{
	package Control
	{
		static bool Throw(string message)
		{
			throw runtime_error(message);
			return true;
		}
		static void Exit(int code)
		{
			exit(code);
		}
	};
}

#endif