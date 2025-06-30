#ifndef TIME_H
#define TIME_H

#include <stdint.h>
#include <sstream>
#include <iomanip>
#include <chrono>

class OKTime
{
public:

	static float m_DeltaTime;
	static float m_UnscaledDeltaTime;
	static float m_TimeScale;
	static float m_RealTimeSinceStartUp;
	static float m_Time;
	static uint32_t m_FrameCount;

public:

	// CLASS FUNCTION(s)

	OKTime() = default;
	OKTime(const OKTime&) = delete;
	OKTime& operator=(const OKTime&) = delete;


	// BASE FUNCTION(s)

	static inline float GetDeltaTime() { return m_DeltaTime; }
	static inline float GetUnscaledDeltaTime() { return m_UnscaledDeltaTime; }
	static inline float GetTimeScale() { return m_TimeScale; }
	static inline float GetRealTimeSinceStartUp() { return m_RealTimeSinceStartUp; }
	static inline float GetTime() { return m_Time; }
	static inline uint32_t GetFrameCount() { return m_FrameCount; }

	static inline std::string GetLocalTimeFormat()
	{
		//auto t = std::time(0);
		//auto tm = *std::localtime(&t);
		//auto fix = localtime_s(&t, &tm);

		//std::ostringstream os;
		//os << std::put_time(&tm, "%H:%M:%S %d=%m-%Y");
		//return os.str();
	}

};

#endif