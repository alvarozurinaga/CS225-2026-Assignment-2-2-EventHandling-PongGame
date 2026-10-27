/**
 * @author alvaro.zurinaga
 * @brief Draw a paddle or ball using its position component
 */

#ifndef RENDER_COMPONENT_H
#define RENDER_COMPONENT_H

#include "../Framework/component.hh"

/**
 * @brief Draw an entity using its position
 */
class RenderComponent : public Component
{
public:
    enum Shape
    {
        RECTANGLE,
        CIRCLE
    };

private:
    Shape shape;
    float width;
    float height;
    unsigned color;

public:
    /**
     * @brief Set the shape, size and color
     */
    RenderComponent(Shape newShape, float newWidth, float newHeight, unsigned newColor);

    /**
     * @brief Draw the entity at its current position
     */
    virtual void Draw();

    /**
     * @brief Destroy the render component
     */
    virtual ~RenderComponent();
};

#endif
