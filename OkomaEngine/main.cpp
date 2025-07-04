#include "HeaderManager.h"
#include "WindowConstants.h"
#include "Timer.h"
#include "TimeStepConstants.h"
#include "OKTime.h"
#include "SceneManager.h"

#include <iostream>

int main()
{
	// NOTE: Check the window has been inited
	#pragma region Window SetUp

	try
	{
		InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE_NAME);
		SetWindowState(FLAG_WINDOW_RESIZABLE);
		if (!IsWindowReady()) { throw; }
	}
	catch (const std::bad_exception& e)
	{
		std::cerr << "Window Bad Exception: " << e.what() << std::endl;
	}

	#pragma endregion

	// NOTE: Check the Audio has been inited
	#pragma region Audio SetUp

	try
	{
		InitAudioDevice();
		if (!IsAudioDeviceReady()) { throw; }
	}
	catch (const std::bad_exception& e)
	{
		std::cerr << "Audio Bad Exception: " << e.what() << std::endl;
	}

	#pragma endregion

	// NOTE: Time Init
	float g_StartTime = 0.0f;
	#pragma region Time SetUp

	g_StartTime = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch().count() / 1000000.f;
	OKTime::m_TimeScale = 1;

	#pragma endregion

	// NOTE: Check the Scene Manager has been inited
	SceneManager* g_SceneManager = new SceneManager();
	#pragma region Scene Manager SetUp

	try
	{
		if (g_SceneManager == nullptr)
		{
			throw;
		}
	}
	catch (...)
	{
		std::cerr << "Set up for Scene Manager has Failed" << std::endl;
	}




	#pragma endregion

	rlDisableBackfaceCulling();

	Timer* m_Timer = new Timer();
	float m_Accumulator = 0.f;
	float m_SimpleCounter = 0.f;

	// NOTE: Plinko
	while (!WindowShouldClose())
	{

		// NOTE: Fixing the Time step with a force accumulator
		m_Accumulator += m_Timer->GetDeltaTime();
		m_SimpleCounter += m_Timer->GetDeltaTime();

		// NOTE: Make sure the framerate is right to the accumualtor
		g_SceneManager->Update(GetFrameTime());
		g_SceneManager->Draw();

		if (m_Accumulator >= FPS_60)
		{

			m_Accumulator -= FPS_60;
		}
		
		// NOTE: Simple Counter

		//printf("DeltaTime: %f\n", m_Timer->GetDeltaTime());
		//printf("FrameTime: %f\n\n", GetFrameTime());
		// NOTE: Tick the timer from the last frame
		m_Timer->Tick();


		//// NOTE: Start of Delta Time
		//auto startTime = std::chrono::high_resolution_clock::now();
		//// NOTE: End of Delta Time
		//auto endTime = std::chrono::high_resolution_clock::now();

		//// NOTE: Delta Time Assinging
		//auto start = std::chrono::time_point_cast<std::chrono::microseconds>(startTime).time_since_epoch().count();
		//auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTime).time_since_epoch().count();

		//OKTime::m_UnscaledDeltaTime = (float)(end - start) / 1000000.f;
		//OKTime::m_DeltaTime = OKTime::m_UnscaledDeltaTime * OKTime::m_TimeScale;

		//OKTime::m_RealTimeSinceStartUp = end / 1000000.f - g_StartTime;
		//OKTime::m_Time = OKTime::m_RealTimeSinceStartUp * OKTime::m_TimeScale;
		//OKTime::m_FrameCount++;

	}

	delete g_SceneManager;

	CloseAudioDevice();
	CloseWindow();

	return 0;
}