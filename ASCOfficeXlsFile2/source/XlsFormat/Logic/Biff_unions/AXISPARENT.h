#pragma once

#include <Logic/CompositeObject.h>

namespace XLS
{;


// Logical representation of AXISPARENT union of records 
class AXISPARENT: public CompositeObject
{
	BASE_OBJECT_DEFINE_CLASS_NAME(AXISPARENT)
public:
	AXISPARENT();
	~AXISPARENT();

	BaseObjectPtr clone();

	virtual const bool loadContent(BinProcessor& proc);

};

} // namespace XLS
