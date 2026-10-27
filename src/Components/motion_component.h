/**
 * @author alvaro.zurinaga
 * @brief Move an entity using a simple velocity without physics
 */

#ifndef MOTION_COMPONENT_H
#define MOTION_COMPONENT_H

#include "../Framework/component.hh"

/**
 * @brief Store and apply an entity velocity
 */
class MotionComponent : public Component
{
private:
    float velocityX;
    float velocityY;

public:
    /**
     * @brief Initialize the movement velocity
     */
    MotionComponent(float startX, float startY);

    /**
     * @brief Move the entity using its velocity
     */
    void move(float seconds);

    /**
     * @brief Set the movement velocity
     */
    void setVelocity(float newX, float newY);

    /**
     * @brief Return the horizontal velocity
     */
    float getVelocityX() const;

    /**
     * @brief Return the vertical velocity
     */
    float getVelocityY() const;

    /**
     * @brief Destroy the motion component
     */
    virtual ~MotionComponent();
};

#endif
