#include "TimeHandler.h"

std::chrono::time_point<std::chrono::high_resolution_clock> TimeHandler::end;
std::chrono::time_point<std::chrono::high_resolution_clock> TimeHandler::start;

void TimeHandler::Start() {
	start = std::chrono::high_resolution_clock::now();
}


void TimeHandler::End() {
	end = std::chrono::high_resolution_clock::now();
}

void TimeHandler::Reset() {
	Start();
}

int TimeHandler::GetElapsedTime() {
	End();
	std::chrono::duration<double> elapsed = end - start;
	return elapsed.count();
}