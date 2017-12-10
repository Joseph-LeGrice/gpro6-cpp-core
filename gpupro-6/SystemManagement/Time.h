#pragma once
#include "SystemManagement/ISystem.h"
#include <chrono>

typedef std::chrono::steady_clock::time_point TimePoint;
typedef std::chrono::duration<float, std::chrono::seconds::period> Seconds;

class Time
{
friend class SystemManager;

public:
    Time();
    ~Time();

	static float FixedTimeStep();
    static float DeltaTimeStep();

private:
    static StaticPointer<Time> s_instance;

	TimePoint m_time;
	Seconds m_deltaTime;
	Seconds m_fixedTimestep;
	Seconds m_latency;

	void AdvanceFrame();
	bool ShouldAdvanceFixedStep();
};

