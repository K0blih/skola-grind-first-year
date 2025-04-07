#pragma once
class Shield {
public:
	Shield() = default;
	Shield(float defence);

	float getDefence();

private:
	float defence;
};