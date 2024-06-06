#pragma once
#include <GLFW/glfw3.h>

#define TIME_MANAGER TimeManager::Instance()

class TimeManager {
private:

	float deltaTime;
	int FPS;
	float frameTime;
	float currentTime;
	float timeToReset;
	float scaleTime;

	TimeManager();

	TimeManager(const TimeManager&) = delete;
	TimeManager& operator =(const TimeManager&) = delete;

public:

	inline static TimeManager& Instance()
	{
		static TimeManager timeManager;
		return timeManager;
	}

	void Update();

	void Pause();

	void AccelerateScaleTime();
	void DeclerateScaleTime();

	inline float GetCurrentTime() const { return currentTime; }
	inline float GetDeltaTime() const { return deltaTime; }
};