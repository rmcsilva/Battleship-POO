#pragma once
class FishModel
{
	static const int cooldownTime = 3;
	bool onCooldown = false;
	int countdown = cooldownTime;
public:
	FishModel()=default;

	bool hasFish();
	void catchFish();
	void updateCountdown();
};

