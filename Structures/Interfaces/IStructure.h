#ifndef ISTRUCTURE_H
#define ISTRUCTURE_H

#include "config.h"

namespace Structures
{
	template<typename K,class T> interface IStructure
	{
		typedef K KeyType;
		typedef T ValueType;

		virtual void Add(T*)=0;
		virtual T* Get(K)=0;
		virtual void Delete(K)=0;

		virtual vector<T*> ToVector()=0;

		virtual uint Size()=0;

		virtual T* Begin()=0;
		virtual T* Next()=0;
	};
}

#endif
