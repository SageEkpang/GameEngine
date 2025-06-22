#include "OKTime.h"

float OKTime::m_DeltaTime = 0.0f;
float OKTime::m_UnscaledDeltaTime = 0.0f;
float OKTime::m_TimeScale = 1.0f;
float OKTime::m_Time = 0.0f;
float OKTime::m_RealTimeSinceStartUp = 0.0f;
uint32_t OKTime::m_FrameCount = 0;