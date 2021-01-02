#pragma once
#include <chrono>

static class TimeHandler {
public:

	static void Start();
	static int GetElapsedTime();
	static void Reset();

private:
	static std::chrono::time_point<std::chrono::high_resolution_clock> start;
	static std::chrono::time_point<std::chrono::high_resolution_clock> end;

	static void ResetClock();
	static void End();
};