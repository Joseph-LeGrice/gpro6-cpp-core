#pragma once
#include "Systems\GameSystem.h"
#include <chrono>

typedef std::chrono::steady_clock::time_point TimePoint;
typedef std::chrono::duration<float, std::chrono::seconds::period> Seconds;

class TimeSystem : public ISystem
{
	REGISTER_SUBSYSTEM(TimeSystem);

public:
	float FixedTimeStep();
	float DeltaTimeStep();

	void AdvanceFrame();
	bool ShouldAdvanceFixedStep();

private:
	TimePoint m_time;
	Seconds m_deltaTime;
	Seconds m_fixedTimestep;
	Seconds m_latency;
};

