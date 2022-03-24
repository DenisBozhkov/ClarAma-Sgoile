#ifndef IDATAMANAGER_H
#define IDATAMANAGER_H

#include "Headers/ModelSet.h"

#include "Models.h"
#include "Functions.h"

using namespace Functions;
using namespace Models;
using namespace Structures;

namespace DataManagers
{
	template<typename K,class T,class S> einterface IDataManager
	{
		public:
			S Models;

			virtual void Read()=0;
			virtual void Save()=0;
		protected:
			inline static path saveDir=path("../Save/Saved");
	};
}

#endif