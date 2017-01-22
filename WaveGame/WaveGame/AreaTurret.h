#ifndef _AREATURRET_INCLUDED
#define _AREATURRET_INCLUDED

#include "BaseTurret.h"

class AreaTurret : public BaseTurret
{
public:
	AreaTurret(Point middle, float width, float height, int damage, unsigned int firerate, float range, unsigned int cost, const list<string> &sprites);
	virtual void think() override;
};

#endif