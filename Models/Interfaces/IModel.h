#ifndef IMODEL_H
#define IMODEL_H

#include "config.h"
#include "Enums/Enums.h"

namespace Models
{
	template<typename IdType> interface IModel
	{
		IModel()=delete;

		virtual IdType Id()
		{ return id; }
		private:
			IdType id;
		protected:
			IModel(IdType id)
				:id(id){ }
	};
}

#endif
