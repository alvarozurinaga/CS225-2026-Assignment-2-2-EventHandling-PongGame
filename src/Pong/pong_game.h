/**
 * @author alvaro.zurinaga
 * @brief Own one round and connect entities to the event managers
 */

#ifndef PONG_GAME_H
#define PONG_GAME_H

#include "ball.h"
#include "player.h"
#include "cpu.h"
#include "input_event_manager.h"
#include "collision_event_manager.h"

/**
 * @brief Manage the entities and events for one round
 */
class PongGame
{
private:
    Ball ball;
    Player player;
    CPU cpu;
    InputEventManager inputEvents;
    CollisionEventManager collisionEvents;
    EventHandler<PongGame, CollisionEvent> goalHandler;
    double accumulatedTime;
    bool gameOver;

    /**
     * @brief End the round when the ball reaches a goal
     */
    void onCollision(CollisionEvent* event);

public:
    /**
     * @brief Create a round and register event handlers
     */
    PongGame();

    /**
     * @brief Advance the game simulation
     */
    void Update(float frameTime, bool inputEnabled);

    /**
     * @brief Draw the court, entities and instructions
     */
    void Draw();

    /**
     * @brief Return whether the round has ended
     */
    bool isGameOver() const;

    /**
     * @brief Destroy the current round
     */
    ~PongGame();

    /**
     * @brief Prevent copying the game
     */
    PongGame(const PongGame&) = delete;

    /**
     * @brief Prevent assigning another game
     */
    PongGame& operator=(const PongGame&) = delete;
};

#endif
