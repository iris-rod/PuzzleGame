#include "TimeHandler.h"

TimeHandler::TimeHandler() : start(chrono::high_resolution_clock::now()), end(chrono::high_resolution_clock::now()) {

}

void TimeHandler::Start() {
	start = chrono::high_resolution_clock::now();
}

chrono::time_point<chrono::high_resolution_clock> TimeHandler::GetCurrentTime() {
	return chrono::high_resolution_clock::now();
}

void TimeHandler::End() {
	end = chrono::high_resolution_clock::now();
}

void TimeHandler::Reset() {
	Start();
}

int TimeHandler::GetElapsedTime() {
	End();
	chrono::duration<double> elapsed = end - start;
	return elapsed.count();
}