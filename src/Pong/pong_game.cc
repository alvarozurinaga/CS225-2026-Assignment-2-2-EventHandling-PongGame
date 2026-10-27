/**
 * @author alvaro.zurinaga
 * @brief Own one round and connect entities to the event managers
 */

#include "pong_game.h"
#include "pong_settings.h"
#include <AEEngine.h>

PongGame::PongGame()
    : cpu(ball), collisionEvents(ball, player, cpu),
      goalHandler(this, &PongGame::onCollision), accumulatedTime(0.0), gameOver(false)
{
    inputEvents.registerEventHandler(player.getInputHandler());
    // The ball reflects first, then the CPU reacts to the resulting direction
    collisionEvents.registerEventHandler(ball.getCollisionHandler());
    collisionEvents.registerEventHandler(cpu.getCollisionHandler());
    collisionEvents.registerEventHandler(&goalHandler);
}

void PongGame::Update(float frameTime, bool inputEnabled)
{
    if (gameOver || frameTime <= 0.0f)
        return;

    // I avoid a large catch-up loop if the window was paused or dragged
    if (frameTime > 0.25f)
        frameTime = 0.25f;
    accumulatedTime += frameTime;
    inputEvents.setEnabled(inputEnabled);

    while (accumulatedTime >= PongSettings::TIME_STEP && !gameOver)
    {
        inputEvents.update();
        player.Update();
        cpu.Update();
        ball.Update();
        collisionEvents.update();
        accumulatedTime -= PongSettings::TIME_STEP;
    }
}

void PongGame::Draw()
{
    const unsigned white = AEGfxColor(230, 230, 230);
    const unsigned grey = AEGfxColor(125, 125, 125);
    AEGfxRectMinMax(-390.0f, PongSettings::TOP_EDGE,
        390.0f, PongSettings::TOP_EDGE + 5.0f, 0.0f, white);
    AEGfxRectMinMax(-390.0f, PongSettings::BOTTOM_EDGE - 5.0f,
        390.0f, PongSettings::BOTTOM_EDGE, 0.0f, white);

    for (int y = PongSettings::BOTTOM_EDGE + 10; y < PongSettings::TOP_EDGE - 10; y += 24)
        AEGfxRectMinMax(-2.0f, static_cast<float>(y),
            2.0f, static_cast<float>(y + 12), 0.0f, grey);

    // I call the virtual functions through the framework entity interface
    Entity* entities[] = { &player, &cpu, &ball };
    for (int i = 0; i < 3; ++i)
        entities[i]->Draw();

    AEGfxPrint(365, 32, white, "PONG");
    AEGfxPrint(20, 48, grey, "PLAYER");
    AEGfxPrint(730, 48, grey, "CPU");
    AEGfxPrint(12, 565, white, "Move: W / S or Up / Down    Restart: R    Quit: Ctrl + Q");
    AEGfxPrint(12, 580, grey, "A missed ball resets the game");
}

void PongGame::onCollision(CollisionEvent* event)
{
    if (event != NULL && (event->getType() == CollisionEvent::LEFT_GOAL ||
        event->getType() == CollisionEvent::RIGHT_GOAL))
        gameOver = true;
}

bool PongGame::isGameOver() const
{
    return gameOver;
}

PongGame::~PongGame()
{
    // Managers store borrowed handler pointers and never delete them
    // Their vectors are destroyed before the entity members are destroyed
}
