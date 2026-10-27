/**
 * @author alvaro.zurinaga
 * @brief Share the components and boundary checks used by both paddles
 */

#ifndef PADDLE_H
#define PADDLE_H

#include "../Framework/entity.hh"
#include "../Components/position_component.h"
#include "../Components/motion_component.h"
#include "../Components/render_component.h"

/**
 * @brief Provide shared movement and drawing for paddles
 */
class Paddle : public Entity
{
protected:
    PositionComponent* position;
    MotionComponent* motion;
    RenderComponent* renderer;

public:
    /**
     * @brief Initialize the paddle and its components
     */
    explicit Paddle(float startX);

    /**
     * @brief Move the paddle within the court boundaries
     */
    virtual void Update() override;

    /**
     * @brief Draw the paddle
     */
    virtual void Draw() override;

    /**
     * @brief Return the paddle position
     */
    const PositionComponent& getPosition() const;

    /**
     * @brief Return the paddle position
     */
    PositionComponent& getPosition();

    /**
     * @brief Destroy the paddle
     */
    virtual ~Paddle();

    /**
     * @brief Prevent copying the paddle
     */
    Paddle(const Paddle&) = delete;

    /**
     * @brief Prevent assigning another paddle
     */
    Paddle& operator=(const Paddle&) = delete;
};

#endif
