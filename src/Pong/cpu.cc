/**
 * @author alvaro.zurinaga
 * @brief Start and stop simple ball tracking in response to collisions
 */

#include "cpu.h"
#include "ball.h"
#include "pong_settings.h"
#include <cmath>

CPU::CPU(const Ball& gameBall)
    : Paddle(PongSettings::CPU_X), ball(gameBall), tracking(false),
      collisionHandler(this, &CPU::onCollision)
{
}

void CPU::Update()
{
    float velocity = 0.0f;
    if (tracking)
    {
        const float difference = ball.getPosition().getY() - position->getY();
        const float maxStep = PongSettings::CPU_SPEED * PongSettings::TIME_STEP;
        // I limit the last step so the CPU does not shake around its target
        if (std::fabs(difference) <= maxStep)
            velocity = difference / PongSettings::TIME_STEP;
        else if (difference > 0.0f)
            velocity = static_cast<float>(PongSettings::CPU_SPEED);
        else
            velocity = -static_cast<float>(PongSettings::CPU_SPEED);
    }
    motion->setVelocity(0.0f, velocity);
    Paddle::Update();
}

IEventHandler* CPU::getCollisionHandler()
{
    return &collisionHandler;
}

void CPU::onCollision(CollisionEvent* event)
{
    if (event == NULL)
        return;

    tracking = event->getType() == CollisionEvent::PLAYER_PADDLE;
    if (!tracking)
        motion->setVelocity(0.0f, 0.0f);
}

bool CPU::isTracking() const
{
    return tracking;
}

CPU::~CPU()
{
}
