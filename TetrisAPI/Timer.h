#pragma once
#include <chrono>

using namespace std::chrono;

namespace TetrisAPI
{
	class Timer
	{
	public:
		Timer(const uint16_t& durationInMilliseconds);

		inline bool IsActive() const { return m_isActive; }
		milliseconds GetElapsedTime() const;
		bool ReachedThreshold() const;

		void Start();
		void Stop();
	private:
		steady_clock::time_point m_startTime;
		bool m_isActive;
		const milliseconds m_duration;
	};
}

