#pragma once

class Time;
class SystemContainer;

class GameLoop
{
public:
	GameLoop::GameLoop(Time& time) : m_time(time) { }
	GameLoop(const GameLoop&) = delete;
    ~GameLoop() = default;

	int Run(SystemContainer& systems);
	void Stop();

private:
	Time& m_time;
	bool m_running;
};
