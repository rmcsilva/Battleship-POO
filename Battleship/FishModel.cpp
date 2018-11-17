#include "stdafx.h"
#include "FishModel.h"

bool FishModel::hasFish(){return !onCooldown;}

void FishModel::catchFish()
{
	if (hasFish()) onCooldown = true;
}

void FishModel::updateCountdown()
{
	if (!hasFish())
	{
		countdown--;
		if (countdown==0)
		{
			onCooldown = false;
			countdown = cooldownTime;
		}
	}
}
