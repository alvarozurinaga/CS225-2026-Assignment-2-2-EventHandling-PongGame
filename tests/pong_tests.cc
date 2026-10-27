/**
 * @author alvaro.zurinaga
 * @brief Declare behavioral checks for input, collisions and round lifetime
 */

#include "pong_tests.h"
#include "../src/Pong/pong_settings.h"
#include <AEEngine.h>
#include <cmath>
#include <iostream>

namespace
{
    int failures = 0;
    int checks = 0;
}

CollisionRecorder::CollisionRecorder()
    : handler(this, &CollisionRecorder::onCollision)
{
    for (int i = 0; i < 6; ++i)
        counts[i] = 0;
}

void CollisionRecorder::onCollision(CollisionEvent* event)
{
    ++counts[event->getType()];
}

IEventHandler* CollisionRecorder::getHandler()
{
    return &handler;
}

PongFixture::PongFixture()
    : cpu(ball), collisions(ball, player, cpu)
{
    input.registerEventHandler(player.getInputHandler());
    collisions.registerEventHandler(ball.getCollisionHandler());
    collisions.registerEventHandler(cpu.getCollisionHandler());
    collisions.registerEventHandler(recorder.getHandler());
}

void PongFixture::step(int count)
{
    for (int i = 0; i < count; ++i)
    {
        player.Update();
        cpu.Update();
        ball.Update();
        collisions.update();
    }
}

void PongFixture::followBallWithPlayer()
{
    const float difference = ball.getPosition().getY() - player.getPosition().getY();
    int direction = 0;
    if (difference > 1.0f)
        direction = 1;
    else if (difference < -1.0f)
        direction = -1;
    InputEvent event(direction);
    input.notifyEvent(&event);
    step(1);
}

void check(bool condition, const char* description)
{
    ++checks;
    if (!condition)
    {
        ++failures;
        std::cout << "FAIL: " << description << '\n';
    }
}

bool near(float left, float right)
{
    return std::fabs(left - right) < 0.001f;
}

void testInput()
{
    EngineStub::reset();
    PongFixture fixture;
    EngineStub::setKey('W', true);
    fixture.input.update();
    fixture.player.Update();
    check(near(fixture.player.getPosition().getY(), 3.0f), "W moves up through an input event");
    fixture.input.update();
    fixture.player.Update();
    check(near(fixture.player.getPosition().getY(), 6.0f), "Holding W keeps moving");
    EngineStub::setKey('W', false);
    fixture.input.update();
    fixture.player.Update();
    check(near(fixture.player.getPosition().getY(), 6.0f), "Releasing the key stops movement");

    EngineStub::setKey('S', true);
    fixture.input.update();
    fixture.player.Update();
    check(near(fixture.player.getPosition().getY(), 3.0f), "S moves down");
    EngineStub::setKey('W', true);
    fixture.input.update();
    fixture.player.Update();
    check(near(fixture.player.getPosition().getY(), 3.0f), "Opposite directions cancel");
    EngineStub::reset();
    EngineStub::setKey(VK_UP, true);
    fixture.input.update();
    fixture.player.Update();
    check(near(fixture.player.getPosition().getY(), 6.0f), "Up arrow uses the same movement event");
    EngineStub::reset();
    EngineStub::setKey(VK_DOWN, true);
    fixture.input.update();
    fixture.player.Update();
    check(near(fixture.player.getPosition().getY(), 3.0f), "Down arrow uses the same movement event");
    fixture.input.setEnabled(false);
    fixture.input.update();
    fixture.player.Update();
    check(near(fixture.player.getPosition().getY(), 3.0f), "Menu capture sends a stop event");

    CollisionEvent unrelated(CollisionEvent::TOP_WALL);
    fixture.input.notifyEvent(&unrelated);
    fixture.player.Update();
    check(near(fixture.player.getPosition().getY(), 3.0f), "Generic handler ignores an unrelated event type");
    InputEvent up(1);
    fixture.input.notifyEvent(&up);
    fixture.player.Update();
    check(near(fixture.player.getPosition().getY(), 6.0f), "Player accepts movement without a keyboard device");
    EngineStub::reset();
}

void testPaddleLimits()
{
    PongFixture fixture;
    InputEvent up(1);
    fixture.input.notifyEvent(&up);
    for (int i = 0; i < 1000; ++i)
        fixture.player.Update();
    check(near(fixture.player.getPosition().getY(), PongSettings::TOP_EDGE - 40.0f),
        "Player top edge stays inside the court");
    InputEvent down(-1);
    fixture.input.notifyEvent(&down);
    for (int i = 0; i < 1000; ++i)
        fixture.player.Update();
    check(near(fixture.player.getPosition().getY(), PongSettings::BOTTOM_EDGE + 40.0f),
        "Player bottom edge stays inside the court");

    CollisionEvent start(CollisionEvent::PLAYER_PADDLE);
    fixture.cpu.onCollision(&start);
    fixture.ball.getPosition().setPosition(0.0f, 500.0f);
    for (int i = 0; i < 1000; ++i)
        fixture.cpu.Update();
    check(near(fixture.cpu.getPosition().getY(), PongSettings::TOP_EDGE - 40.0f),
        "CPU is clamped at the top");
    fixture.ball.getPosition().setPosition(0.0f, -500.0f);
    for (int i = 0; i < 1000; ++i)
        fixture.cpu.Update();
    check(near(fixture.cpu.getPosition().getY(), PongSettings::BOTTOM_EDGE + 40.0f),
        "CPU is clamped at the bottom");
}

void testPaddleCollisions()
{
    PongFixture fixture;
    check(!fixture.cpu.isTracking(), "CPU starts stationary");
    fixture.ball.getPosition().setPosition(-335.0f, 10.0f);
    fixture.step(1);
    check(fixture.recorder.counts[CollisionEvent::PLAYER_PADDLE] == 1, "Player contact creates an event");
    check(near(fixture.ball.getMotion().getVelocityX(), 280.0f), "Player contact reflects horizontal velocity");
    check(fixture.cpu.isTracking(), "Player contact starts CPU tracking");
    const float oldCPUY = fixture.cpu.getPosition().getY();
    fixture.cpu.Update();
    check(fixture.cpu.getPosition().getY() > oldCPUY, "Tracking CPU follows the ball vertically");
    fixture.collisions.update();
    check(fixture.recorder.counts[CollisionEvent::PLAYER_PADDLE] == 1,
        "A separating ball does not trigger another player contact");

    fixture.ball.getPosition().setPosition(335.0f, fixture.cpu.getPosition().getY());
    fixture.ball.getMotion().setVelocity(280.0f, 170.0f);
    fixture.step(1);
    check(fixture.recorder.counts[CollisionEvent::CPU_PADDLE] == 1, "CPU contact creates an event");
    check(near(fixture.ball.getMotion().getVelocityX(), -280.0f), "CPU contact reflects horizontal velocity");
    check(!fixture.cpu.isTracking(), "CPU contact stops tracking");
    const float stoppedY = fixture.cpu.getPosition().getY();
    fixture.cpu.Update();
    check(near(fixture.cpu.getPosition().getY(), stoppedY), "Stopped CPU does not drift");

    PongFixture miss;
    miss.ball.getPosition().setPosition(-335.0f, 100.0f);
    miss.step(1);
    check(miss.recorder.counts[CollisionEvent::PLAYER_PADDLE] == 0, "Ball above the player misses the paddle");
    check(miss.ball.getMotion().getVelocityX() < 0.0f, "A miss does not reflect the ball");
    miss.ball.getPosition().setPosition(335.0f, -100.0f);
    miss.ball.getMotion().setVelocity(280.0f, -170.0f);
    miss.step(1);
    check(miss.recorder.counts[CollisionEvent::CPU_PADDLE] == 0, "Ball below the CPU misses the paddle");
}

void testWallCollisions()
{
    PongFixture fixture;
    CollisionEvent start(CollisionEvent::PLAYER_PADDLE);
    fixture.cpu.onCollision(&start);
    fixture.ball.getPosition().setPosition(0.0f, 222.75f);
    fixture.step(1);
    check(fixture.recorder.counts[CollisionEvent::TOP_WALL] == 1, "Top contact creates an event");
    check(near(fixture.ball.getPosition().getY(), 223.0f), "Top correction keeps the ball inside");
    check(near(fixture.ball.getMotion().getVelocityY(), -static_cast<float>(PongSettings::BALL_SPEED_Y)),
        "Top contact reflects vertical velocity");
    check(!fixture.cpu.isTracking(), "Top contact stops the CPU");
    fixture.collisions.update();
    check(fixture.recorder.counts[CollisionEvent::TOP_WALL] == 1, "Top contact is not repeated while separating");

    fixture.cpu.onCollision(&start);
    fixture.ball.getPosition().setPosition(0.0f, -252.75f);
    fixture.step(1);
    check(fixture.recorder.counts[CollisionEvent::BOTTOM_WALL] == 1, "Bottom contact creates an event");
    check(near(fixture.ball.getPosition().getY(), -253.0f), "Bottom correction keeps the ball inside");
    check(near(fixture.ball.getMotion().getVelocityY(), static_cast<float>(PongSettings::BALL_SPEED_Y)),
        "Bottom contact reflects vertical velocity");
    check(!fixture.cpu.isTracking(), "Bottom contact stops the CPU");
    const float speedSquared = fixture.ball.getMotion().getVelocityX() * fixture.ball.getMotion().getVelocityX()
        + fixture.ball.getMotion().getVelocityY() * fixture.ball.getMotion().getVelocityY();
    check(near(speedSquared, static_cast<float>(PongSettings::BALL_SPEED_X * PongSettings::BALL_SPEED_X
        + PongSettings::BALL_SPEED_Y * PongSettings::BALL_SPEED_Y)), "Reflections preserve total speed");
}

void testOpeningRally()
{
    PongFixture fixture;
    for (int step = 0; step < 1000; ++step)
    {
        fixture.followBallWithPlayer();

        if (fixture.recorder.counts[CollisionEvent::CPU_PADDLE] > 0 ||
            fixture.recorder.counts[CollisionEvent::LEFT_GOAL] > 0 ||
            fixture.recorder.counts[CollisionEvent::RIGHT_GOAL] > 0)
            break;
    }

    check(fixture.recorder.counts[CollisionEvent::PLAYER_PADDLE] == 1,
        "A moving player can return the opening serve");
    check(fixture.recorder.counts[CollisionEvent::TOP_WALL] == 1,
        "The opening rally includes a real wall bounce");
    check(fixture.recorder.counts[CollisionEvent::CPU_PADDLE] == 1,
        "CPU returns the opening rally after the ball crosses the full court");
    check(fixture.recorder.counts[CollisionEvent::RIGHT_GOAL] == 0,
        "CPU does not lose the opening rally after stopping on the wall bounce");
}

void testLongRally()
{
    PongFixture fixture;
    for (int step = 0; step < 4000; ++step)
    {
        fixture.followBallWithPlayer();
        if (fixture.recorder.counts[CollisionEvent::CPU_PADDLE] >= 5 ||
            fixture.recorder.counts[CollisionEvent::LEFT_GOAL] > 0 ||
            fixture.recorder.counts[CollisionEvent::RIGHT_GOAL] > 0)
            break;
    }

    check(fixture.recorder.counts[CollisionEvent::CPU_PADDLE] == 5,
        "CPU returns five consecutive full-court shots");
    check(fixture.recorder.counts[CollisionEvent::PLAYER_PADDLE] == 5,
        "The test player reaches each return using normal movement speed");
    check(fixture.recorder.counts[CollisionEvent::TOP_WALL] > 0 &&
        fixture.recorder.counts[CollisionEvent::BOTTOM_WALL] > 0,
        "The long rally includes both top and bottom wall bounces");
    check(fixture.recorder.counts[CollisionEvent::RIGHT_GOAL] == 0,
        "CPU keeps the rally alive through several exchanges");
}

void testGoals()
{
    PongFixture left;
    left.ball.getPosition().setPosition(-392.0f, 100.0f);
    left.step(1);
    check(left.recorder.counts[CollisionEvent::LEFT_GOAL] == 1, "Left side creates a game-over event");
    check(left.ball.getMotion().getVelocityX() < 0.0f, "Left goal does not reflect the ball");
    PongFixture right;
    right.ball.getPosition().setPosition(392.0f, -100.0f);
    right.ball.getMotion().setVelocity(280.0f, -170.0f);
    right.step(1);
    check(right.recorder.counts[CollisionEvent::RIGHT_GOAL] == 1, "Right side creates a game-over event");
    check(right.ball.getMotion().getVelocityX() > 0.0f, "Right goal does not reflect the ball");
}

void testRoundLifetime()
{
    EngineStub::reset();
    PongGame oneFrame;
    oneFrame.Update(PongSettings::TIME_STEP * 12.0f, false);
    oneFrame.Draw();
    const float oneX = EngineStub::getCircleX();
    const float oneY = EngineStub::getCircleY();
    PongGame manyFrames;
    for (int i = 0; i < 12; ++i)
        manyFrames.Update(PongSettings::TIME_STEP, false);
    manyFrames.Draw();
    check(near(oneX, EngineStub::getCircleX()) && near(oneY, EngineStub::getCircleY()),
        "Fixed steps give the same movement across different frame rates");
    check(near(oneX, -28.0f) && near(oneY, PongSettings::BALL_SPEED_Y * 0.1f),
        "Motion uses elapsed seconds");
    manyFrames.Update(0.0f, false);
    manyFrames.Update(-1.0f, false);
    manyFrames.Draw();
    check(near(oneX, EngineStub::getCircleX()), "Zero and negative frame times do not move the ball");

    int completedRounds = 0;
    for (int round = 0; round < 100; ++round)
    {
        PongGame game;
        if (!game.isGameOver())
        {
            for (int frame = 0; frame < 400 && !game.isGameOver(); ++frame)
                game.Update(1.0f / 60.0f, false);
            if (game.isGameOver())
                ++completedRounds;
        }
    }
    check(completedRounds == 100, "Repeated rounds reach game over and destroy their subscriptions cleanly");
    PongGame fresh;
    fresh.Draw();
    check(!fresh.isGameOver() && near(EngineStub::getCircleX(), 0.0f)
        && near(EngineStub::getCircleY(), 0.0f), "Reconstructing the round resets game state and ball position");
}

int main()
{
    testInput();
    testPaddleLimits();
    testPaddleCollisions();
    testWallCollisions();
    testOpeningRally();
    testLongRally();
    testGoals();
    testRoundLifetime();
    std::cout << checks << " checks, " << failures << " failures\n";
    return failures == 0 ? 0 : 1;
}
