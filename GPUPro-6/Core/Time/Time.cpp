#include "stdafx.h"
#include <iostream>
#include "Time.h"

using namespace std::chrono;

StaticPointer<Time> Time::s_instance;

Time::Time()
{
	m_fixedTimestep = Seconds(16.0f);
	m_deltaTime = Seconds(0.0f);
	m_latency = Seconds(0.0f);
	using clock = std::chrono::high_resolution_clock;
	m_time = clock::now();
}

Time::~Time()
{
}

float Time::FixedTimeStep()
{
	return s_instance->m_fixedTimestep.count();
}

float Time::DeltaTimeStep()
{
	return s_instance->m_deltaTime.count();
}

bool Time::ShouldAdvanceFixedStep()
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

void Time::AdvanceFrame()
{
	using clock = std::chrono::high_resolution_clock;
	TimePoint thisTime = clock::now();
	m_deltaTime = duration_cast<Seconds>(thisTime - m_time);
	m_latency += m_deltaTime;
	m_time = thisTime;
}
