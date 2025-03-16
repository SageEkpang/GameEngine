#include "Timer.h"

#include "Timer.h"

Timer::Timer()
{
	m_StartClock = high_resolution_clock::now();
	m_LastFrame = steady_clock::now();
}

Timer::~Timer()
{
	Stop();
}

float Timer::GetDeltaTime()
{
	return duration<float>(steady_clock::now() - m_LastFrame).count();
}

void Timer::Tick()
{
	m_LastFrame = steady_clock::now();
}

void Timer::Stop()
{
	//// Get the Current time when the timer is deconstructed
	// auto t_EndTimePoint = high_resolution_clock::now();

	// // Get the Time in Microseconds since the start of the timer and return the Count of that Time
	// auto t_Start = time_point_cast<microseconds>(m_StartClock).time_since_epoch().count();

	// // Same with the Start Time but with the EndTimePoint
	// auto t_End = time_point_cast<microseconds>(t_EndTimePoint).time_since_epoch().count();

	// Calculate the time taken from start to end (End - Start) (End will always be a higher time)

	// auto Duration = t_End - t_Start; // Microseconds
	// double ms = Duration * 0.001; // Milliseconds (Microseconds to Milliseconds)

	// Output the Microseconds and Milliseconds of the Process
	// std::cout << "Microseconds: " << Duration << " us (" << ms << "ms)\n";
	// std::string t_Output = "Microseconds: " + std::to_string(Duration) + " us (" + std::to_string(ms) + "ms)\n";
	// OutputDebugStringA(t_Output.c_str());
}
