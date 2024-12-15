#include "Timer.h"

using namespace TetrisAPI;

Timer::Timer(const uint16_t& durationInMilliseconds) :
	m_duration{ milliseconds(durationInMilliseconds) },
	m_isActive{ false }
{
}

milliseconds Timer::GetElapsedTime() const
{
	auto currentTime{ high_resolution_clock::now() };
	return duration_cast<milliseconds>(currentTime - m_startTime);
}

bool Timer::ReachedThreshold() const
{
	return GetElapsedTime() >= m_duration;
}

void Timer::Start()
{
	m_startTime = high_resolution_clock::now();
	m_isActive = true;
}

void Timer::Stop()
{
	m_isActive = false;
}
