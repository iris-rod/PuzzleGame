#include "TimeHandler.h"

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