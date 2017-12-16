#pragma once

class GameLoop
{
public:
    GameLoop() = default;
    ~GameLoop() = default;

    static int Run();
    static void Stop();

private:
    static StaticPointer<GameLoop> s_instance;

    bool m_running;
    int InternalRun();
    void InternalStop();
};
