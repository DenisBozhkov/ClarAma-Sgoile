#ifndef LABEL_H
#define LABEL_H

#include "../../Interfaces/IComponent.h"

BEGIN
eclass Label:public IComponent
{
	public:
		enum Align { Left,Center,Right };
		P(Label,std::string) Text;
		P(Label,Align) Alignment;
		virtual void Create() override;
		Label();
	protected:
		virtual void initProperties() override;
}
END

#endif