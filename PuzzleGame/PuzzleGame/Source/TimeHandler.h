#pragma once
#include <chrono>

using namespace std;

class TimeHandler {
public:
	TimeHandler();
	int GetElapsedTime();
	void Reset();
	chrono::time_point<chrono::high_resolution_clock> GetCurrentTime();

private:
	chrono::time_point<chrono::high_resolution_clock> start;
	chrono::time_point<chrono::high_resolution_clock> end;

	void End();
	void Start();
};