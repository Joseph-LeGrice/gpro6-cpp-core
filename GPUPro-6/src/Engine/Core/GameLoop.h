#pragma once

#include <vector>
#include <memory>

class Time;
class ISystem;

class GameLoop
{
public:
	GameLoop(Time& time, std::vector<std::unique_ptr<ISystem>> systems) : m_time(time), m_systems(systems) { }
    ~GameLoop() = default;

	int Run();
	void Stop();

private:
	Time& m_time;
	std::vector<std::unique_ptr<ISystem>>& m_systems;
	bool m_running;
};
