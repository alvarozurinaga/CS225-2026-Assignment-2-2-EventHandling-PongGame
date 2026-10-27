/**
 * @author alvaro.zurinaga
 * @brief Share the components and boundary checks used by both paddles
 */

#include "paddle.h"
#include "pong_settings.h"

Paddle::Paddle(float startX)
    : position(new PositionComponent(startX, 0.0f)),
      motion(new MotionComponent(0.0f, 0.0f)),
      renderer(new RenderComponent(RenderComponent::RECTANGLE,
          PongSettings::PADDLE_WIDTH, PongSettings::PADDLE_HEIGHT, 0xffeeeeeeu))
{
    // The entity owns these components once they have been attached
    attach(position);
    attach(motion);
    attach(renderer);
}

void Paddle::Update()
{
    motion->move(PongSettings::TIME_STEP);
    const float halfHeight = PongSettings::PADDLE_HEIGHT * 0.5f;
    float y = position->getY();
    if (y > PongSettings::TOP_EDGE - halfHeight)
        y = PongSettings::TOP_EDGE - halfHeight;
    else if (y < PongSettings::BOTTOM_EDGE + halfHeight)
        y = PongSettings::BOTTOM_EDGE + halfHeight;
    position->setPosition(position->getX(), y);
}

void Paddle::Draw()
{
    renderer->Draw();
}

const PositionComponent& Paddle::getPosition() const
{
    return *position;
}

PositionComponent& Paddle::getPosition()
{
    return *position;
}

Paddle::~Paddle()
{
}
