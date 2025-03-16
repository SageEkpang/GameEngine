#include "HeaderManager.h"
#include "WindowConstants.h"

int main()
{
	// Game Utility (namespace) over Game Manager (class)
	InitWindow(500, 500, "OkomaEngine");
	InitAudioDevice();

	while (!WindowShouldClose())
	{
		// UPDATE

		// DRAW
		BeginDrawing();
		ClearBackground(RAYWHITE);

		

		EndDrawing();
	}
	
	CloseAudioDevice();
	CloseWindow();

	return 0;
}