#pragma once

class IntroFrame : public ChCpp::BaseFrame
{
public:

	void Update()override;

private:

	float animationTime = 0;
	float maxAnimationTime = 0;

};
