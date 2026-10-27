/**
 * @author alvaro.zurinaga
 * @brief Connect the Pong round to the supplied game state callbacks
 */

#include <AEEngine.h>
#include <imgui/imgui.h>
#include "Level 1.h"
#include "../Pong/pong_game.h"
#include "../Pong/pong_settings.h"

int mode = 0;

namespace
{
    PongGame* game = NULL;
}

void Level_1_Load()
{
    AEGfxSetViewRectangle(PongSettings::WINDOW_WIDTH, PongSettings::WINDOW_HEIGHT);
}

void Level_1_Init()
{
    delete game;
    game = new PongGame();
}

void Level_1_Update()
{
    // I keep the framework shortcuts and menu available during gameplay
    KeyboardInput();
    const bool guiActive = ShowFrameworkMenu();
    if (game != NULL)
    {
        game->Update(static_cast<float>(AEGetFrameTime()), !guiActive);
        if (game->isGameOver())
            AESetGameStateNext(AE_GS_RESTART);
    }
}

void Level_1_Render()
{
    // The supplied clear operation must happen before drawing the court
    AEGfxSetClearColor(AEGfxColor(0, 0, 0));
    AEGfxClearBuffer();
    if (game != NULL)
        game->Draw();
}

void Level_1_Free()
{
    delete game;
    game = NULL;
}

void Level_1_Unload()
{
}

void KeyboardInput()
{
    if (AEInputKeyTriggered('R'))
        AESetGameStateNext(AE_GS_RESTART);
    if (AEInputKeyTriggered('Q') && AEInputKeyPressed(AE_KEY_CTRL))
        AESetGameStateNext(AE_GS_QUIT);
}

bool ShowFrameworkMenu()
{
    bool isGuiActive = false;
    mode = 0;

    // show File options 
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Mode")) {

            if (ImGui::MenuItem("Restart", "1"))
                mode = 1;

            ImGui::EndMenu();
        }

        const float mSize = ImGui::GetWindowHeight();
        AEVec2 mouseVP = AEGetMouseData().position + AEVec2((float)AEGetSysWindowWidth() / 2.0f, (float)AEGetSysWindowHeight() / 2.0f);
        const bool inMenu = mouseVP.y >= (AEGetSysWindowHeight() - mSize);
        isGuiActive = ImGui::IsAnyItemActive() || ImGui::IsAnyItemHovered() ||
            ImGui::GetIO().WantCaptureKeyboard || inMenu;

        ImGui::EndMainMenuBar();
    }

    if (mode == 1) {
        AESetGameStateNext(AE_GS_RESTART);
    }

    return isGuiActive;
}

