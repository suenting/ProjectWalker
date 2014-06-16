#include "Widget.h"
#ifndef STEPCOUNTER_H
#define STEPCOUNTER_H

class StepCounter : public Widget
{
public:
	StepCounter();
	virtual ~StepCounter();
	virtual void Render()const;
	virtual void Update();
protected:
	
private:
};

#endif