#pragma once
#include <chrono>

using namespace std::chrono;

class Timer
{
public:
	Timer(const uint16_t& durationInSeconds);

	inline bool IsActive()const { return m_isActive; }
	seconds GetElapsedTime()const;
	bool ReachedThreshold()const;

	void Start();
	void Stop();
private:
	steady_clock::time_point m_startTime;
	bool m_isActive;
	const seconds m_duration;
};

