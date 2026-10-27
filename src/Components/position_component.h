/**
 * @author alvaro.zurinaga
 * @brief Keep an entity position in world coordinates
 */

#ifndef POSITION_COMPONENT_H
#define POSITION_COMPONENT_H

#include "../Framework/component.hh"

/**
 * @brief Store an entity position
 */
class PositionComponent : public Component
{
private:
    float x;
    float y;

public:
    /**
     * @brief Initialize the entity position
     */
    PositionComponent(float startX, float startY);

    /**
     * @brief Return the horizontal position
     */
    float getX() const;

    /**
     * @brief Return the vertical position
     */
    float getY() const;

    /**
     * @brief Set the entity position
     */
    void setPosition(float newX, float newY);

    /**
     * @brief Destroy the position component
     */
    virtual ~PositionComponent();
};

#endif
