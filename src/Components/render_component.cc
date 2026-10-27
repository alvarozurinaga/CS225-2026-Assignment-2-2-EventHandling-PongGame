/**
 * @author alvaro.zurinaga
 * @brief Draw a paddle or ball using its position component
 */

#include "render_component.h"
#include "position_component.h"
#include "../Framework/entity.hh"
#include <AEEngine.h>

RenderComponent::RenderComponent(Shape newShape, float newWidth, float newHeight,
    unsigned newColor)
    : Component("Render"), shape(newShape), width(newWidth), height(newHeight),
      color(newColor)
{
    setOwner(NULL);
}

void RenderComponent::Draw()
{
    if (mOwner == NULL)
        return;

    PositionComponent* position = static_cast<PositionComponent*>(
        mOwner->getComponent("Position"));
    if (position == NULL)
        return;

    // I use both coordinates so the shape follows the entity correctly
    const float x = position->getX();
    const float y = position->getY();
    if (shape == CIRCLE)
        AEGfxCircle(x, y, width * 0.5f, color, 24);
    else
        AEGfxRectMinMax(x - width * 0.5f, y - height * 0.5f,
            x + width * 0.5f, y + height * 0.5f, 0.0f, color);
}

RenderComponent::~RenderComponent()
{
}
