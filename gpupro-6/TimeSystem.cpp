#include "stdafx.h"
#include <iostream>
#include "TimeSystem.h"

using namespace std::chrono;

TimeSystem::TimeSystem()
{
	m_fixedTimestep = Milliseconds(16.0f);
	m_deltaTime = Milliseconds(0.0f);
	m_latency = Milliseconds(0.0f);
	using clock = std::chrono::high_resolution_clock;
	m_time = clock::now();
}

TimeSystem::~TimeSystem()
{
}

float TimeSystem::FixedTimeStep()
{
	return m_fixedTimestep.count();
}

float TimeSystem::DeltaTimeStep()
{
	return m_deltaTime.count();
}

bool TimeSystem::ShouldAdvanceFixedStep()
{
	if (m_latency >= m_fixedTimestep)
	{
		m_latency -= m_fixedTimestep;
		return true;
	}
	else
	{
		return false;
	}
}

void TimeSystem::AdvanceFrame()
{
	using clock = std::chrono::high_resolution_clock;
	TimePoint thisTime = clock::now();
	m_deltaTime = duration_cast<Milliseconds>(thisTime - m_time);
	m_latency += m_deltaTime;
	m_time = thisTime;
}
