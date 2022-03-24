#ifndef ICLASSSUBJECT_H
#define ICLASSSUBJECT_H

#include "IModel.h"

namespace Model
{
	interface IClassSubject:IModel<uint>
	{
		IClassSubject()=delete;

		protected:
			IClassSubject(uint id)
				:IModel(id){ }
	};
}

#endif
