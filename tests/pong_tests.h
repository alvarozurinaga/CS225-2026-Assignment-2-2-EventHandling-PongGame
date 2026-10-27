/**
 * @author alvaro.zurinaga
 * @brief Declare behavioral checks for input, collisions and round lifetime
 */

#ifndef PONG_TESTS_H
#define PONG_TESTS_H

#include "../src/Pong/pong_game.h"

/**
 * @brief Count collision events during tests
 */
class CollisionRecorder
{
private:
    EventHandler<CollisionRecorder, CollisionEvent> handler;

public:
    int counts[6];

    /**
     * @brief Initialize the collision counts
     */
    CollisionRecorder();

    /**
     * @brief Count the received collision
     */
    void onCollision(CollisionEvent* event);

    /**
     * @brief Return the collision recorder handler
     */
    IEventHandler* getHandler();
};

/**
 * @brief Provide a playable round for behavior tests
 */
class PongFixture
{
public:
    Ball ball;
    Player player;
    CPU cpu;
    CollisionRecorder recorder;
    InputEventManager input;
    CollisionEventManager collisions;

    /**
     * @brief Create a test round
     */
    PongFixture();

    /**
     * @brief Advance the test round
     */
    void step(int count);

    /**
     * @brief Move the test player toward the ball
     */
    void followBallWithPlayer();
};

/**
 * @brief Record whether a test expectation passed
 */
void check(bool condition, const char* description);

/**
 * @brief Compare two floating point values
 */
bool near(float left, float right);

/**
 * @brief Check player input behavior
 */
void testInput();

/**
 * @brief Check paddle boundary limits
 */
void testPaddleLimits();

/**
 * @brief Check paddle collisions and CPU reactions
 */
void testPaddleCollisions();

/**
 * @brief Check wall collisions and ball speed
 */
void testWallCollisions();

/**
 * @brief Check the first CPU return
 */
void testOpeningRally();

/**
 * @brief Check several consecutive CPU returns
 */
void testLongRally();

/**
 * @brief Check both goal events
 */
void testGoals();

/**
 * @brief Check timing and round resets
 */
void testRoundLifetime();

/**
 * @brief Run the game behavior tests
 */
int main();

#endif
