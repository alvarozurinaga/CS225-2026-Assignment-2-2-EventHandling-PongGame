/**
 * @author alvaro.zurinaga
 * @brief React to movement events without checking the keyboard directly
 */

#include "player.h"
#include "pong_settings.h"

Player::Player()
    : Paddle(PongSettings::PLAYER_X), inputHandler(this, &Player::onInput)
{
}

IEventHandler* Player::getInputHandler()
{
    return &inputHandler;
}

void Player::onInput(InputEvent* event)
{
    if (event != NULL)
        motion->setVelocity(0.0f,
            static_cast<float>(event->getDirection() * PongSettings::PLAYER_SPEED));
}

Player::~Player()
{
}
