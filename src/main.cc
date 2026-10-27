/**
 * @author alvaro.zurinaga
 * @brief Declare the application entry point
 */

#include "main.h"
#include <AEEngine.h>
#include "Levels\Level 1.h"
#include "Pong/pong_settings.h"

int main()
{
	// I keep the court size fixed to match the world coordinates
	if (AESysInit("CS225 - Event Handling - Pong Game",
        PongSettings::WINDOW_WIDTH, PongSettings::WINDOW_HEIGHT) == false)
	{
		return 1;
	}


	// Add a game state to the game state manager
	AEGameStateMgrAdd(
		GS_LEVEL_1,
		Level_1_Load,
		Level_1_Init,
		Level_1_Update,
		Level_1_Render,
		Level_1_Free,
		Level_1_Unload);

	// Initialize the game state manager
	AEGameStateMgrInit(GS_LEVEL_1);

	AESetFrameRateMax(120.0);
	// Run the engine loop until the user closes the game
	AESysGameLoop();

	// Release engine resources after the game state has been freed
	AESysExit();

	return 0;
}
