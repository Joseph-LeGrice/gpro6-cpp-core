#pragma once
#include "ISystem.h"
#include <chrono>

typedef std::chrono::steady_clock::time_point TimePoint;
typedef std::chrono::duration<float, std::chrono::milliseconds::period> Milliseconds;

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
	Milliseconds m_deltaTime;
	Milliseconds m_fixedTimestep;
	Milliseconds m_latency;
};

