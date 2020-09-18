#ifndef SPENCER_TIMEINTENT_H
#define SPENCER_TIMEINTENT_H

#include "Intent.hpp"
class TimeIntent: public Intent
{
public:
	TimeIntent(void* params);
	virtual ~TimeIntent() override;
	
};


#endif