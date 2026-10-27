/**
 * @author alvaro.zurinaga
 * @brief Connect the Pong round to the supplied game state callbacks
 * Original level scaffold by Thomas Komair
 * Copyright DigiPen Institute of Technology, 2015, All rights reserved
 */

#ifndef LEVEL_1_H_
#define LEVEL_1_H_


#define GS_LEVEL_1 1

/**
 * @brief Set the game view
 */
void Level_1_Load();

/**
 * @brief Create a new round
 */
void Level_1_Init();

/**
 * @brief Update the menu and current round
 */
void Level_1_Update();

/**
 * @brief Clear the screen and draw the game
 */
void Level_1_Render();

/**
 * @brief Delete the current round
 */
void Level_1_Free();

/**
 * @brief Handle the level unload callback
 */
void Level_1_Unload();

/**
 * @brief Process restart and quit shortcuts
 */
void KeyboardInput();

/**
 * @brief Display the menu and report whether it captures input
 */
bool ShowFrameworkMenu();

#endif
