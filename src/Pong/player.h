/**
 * @author alvaro.zurinaga
 * @brief React to movement events without checking the keyboard directly
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "paddle.h"
#include "pong_events.h"
#include "../Framework/event_handlers.hh"

/**
 * @brief Control the player paddle through input events
 */
class Player : public Paddle
{
private:
    EventHandler<Player, InputEvent> inputHandler;

public:
    /**
     * @brief Initialize the player paddle
     */
    Player();

    /**
     * @brief Return the player input event handler
     */
    IEventHandler* getInputHandler();

    /**
     * @brief Set the player movement from an input event
     */
    void onInput(InputEvent* event);

    /**
     * @brief Destroy the player
     */
    virtual ~Player();
};

#endif
