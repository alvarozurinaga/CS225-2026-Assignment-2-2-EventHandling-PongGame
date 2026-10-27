/**
 * @author alvaro.zurinaga
 * @brief Detect contacts and notify the interested entities through events
 */

#include "collision_event_manager.h"
#include "ball.h"
#include "paddle.h"
#include "pong_settings.h"
#include <cmath>

CollisionEventManager::CollisionEventManager(Ball& gameBall, const Paddle& gamePlayer,
    const Paddle& gameCPU)
    : ball(gameBall), player(gamePlayer), cpu(gameCPU)
{
}

bool CollisionEventManager::hitPaddle(const Paddle& paddle, bool isPlayer)
{
    const float direction = ball.getMotion().getVelocityX();
    if ((isPlayer && direction >= 0.0f) || (!isPlayer && direction <= 0.0f))
        return false;

    const float offset = PongSettings::PADDLE_WIDTH * 0.5f + PongSettings::BALL_RADIUS;
    const float face = paddle.getPosition().getX() + (isPlayer ? offset : -offset);
    const float oldX = ball.getPreviousX();
    const float newX = ball.getPosition().getX();
    const bool crossed = isPlayer ? oldX >= face && newX <= face
                                 : oldX <= face && newX >= face;
    if (!crossed || newX == oldX)
        return false;

    // I check the height at the crossing so the ball cannot skip a paddle face
    const float fraction = (face - oldX) / (newX - oldX);
    const float hitY = ball.getPreviousY() +
        (ball.getPosition().getY() - ball.getPreviousY()) * fraction;
    const float reach = PongSettings::PADDLE_HEIGHT * 0.5f + PongSettings::BALL_RADIUS;
    if (std::fabs(hitY - paddle.getPosition().getY()) > reach)
        return false;

    // Placing the ball outside the paddle prevents another hit on the next step
    ball.getPosition().setPosition(face, ball.getPosition().getY());
    return true;
}

void CollisionEventManager::sendCollision(CollisionEvent::Type type)
{
    CollisionEvent event(type);
    notifyEvent(&event);
}

void CollisionEventManager::update()
{
    PositionComponent& position = ball.getPosition();
    const float radius = static_cast<float>(PongSettings::BALL_RADIUS);

    if (position.getY() + radius >= PongSettings::TOP_EDGE &&
        ball.getMotion().getVelocityY() > 0.0f)
    {
        position.setPosition(position.getX(), PongSettings::TOP_EDGE - radius);
        sendCollision(CollisionEvent::TOP_WALL);
    }
    else if (position.getY() - radius <= PongSettings::BOTTOM_EDGE &&
        ball.getMotion().getVelocityY() < 0.0f)
    {
        position.setPosition(position.getX(), PongSettings::BOTTOM_EDGE + radius);
        sendCollision(CollisionEvent::BOTTOM_WALL);
    }

    if (hitPaddle(player, true))
        sendCollision(CollisionEvent::PLAYER_PADDLE);
    else if (hitPaddle(cpu, false))
        sendCollision(CollisionEvent::CPU_PADDLE);

    // Reaching either open side ends the round instead of reflecting the ball
    if (position.getX() - radius <= PongSettings::LEFT_EDGE)
        sendCollision(CollisionEvent::LEFT_GOAL);
    else if (position.getX() + radius >= PongSettings::RIGHT_EDGE)
        sendCollision(CollisionEvent::RIGHT_GOAL);
}
