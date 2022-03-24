#ifndef GRIDCHECKBOX_H
#define GRIDCHECKBOX_H

#include "Visual.h"

class GridCheckbox:public Visual::Checkbox
{
	public:
		GridCheckbox()
			:Checkbox(),
			Row(0),
			Column(0){}
		int Row;
		int Column;
};

#endif