#include "TimeManager.h"

TimeManager::TimeManager() 
{
	FPS = 60;
	frameTime = 1.0f / (float)FPS;
	timeToReset = 6.f;
	scaleTime = 1.0f;

	deltaTime = frameTime * scaleTime;
}

void TimeManager::Update()
{
	if (scaleTime != 0.f)
	{
		currentTime += frameTime;

		if (currentTime >= timeToReset)
		{
			currentTime -= timeToReset;
		}
	}

	deltaTime = frameTime * scaleTime;
}

void TimeManager::Pause()
{
	scaleTime = (scaleTime == 0.f) ? 1.0f : 0.f;
}

void TimeManager::AccelerateScaleTime()
{
	scaleTime *= 1.1f;
}

void TimeManager::DeclerateScaleTime()
{
	scaleTime *= 0.9f;
}