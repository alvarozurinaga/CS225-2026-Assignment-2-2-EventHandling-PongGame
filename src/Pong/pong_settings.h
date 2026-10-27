/**
 * @author alvaro.zurinaga
 * @brief Share the court dimensions and simple movement speeds
 */

#ifndef PONG_SETTINGS_H
#define PONG_SETTINGS_H

namespace PongSettings
{
    enum
    {
        WINDOW_WIDTH = 800,
        WINDOW_HEIGHT = 600,
        LEFT_EDGE = -400,
        RIGHT_EDGE = 400,
        TOP_EDGE = 230,
        BOTTOM_EDGE = -260,
        PLAYER_X = -350,
        CPU_X = 350,
        PADDLE_WIDTH = 14,
        PADDLE_HEIGHT = 80,
        BALL_RADIUS = 7,
        PLAYER_SPEED = 360,
        CPU_SPEED = 260,
        BALL_SPEED_X = 280,
        // I keep a shallow angle so stopping at a wall still allows CPU returns
        BALL_SPEED_Y = 75
    };

    // I use a small fixed step so collisions behave the same at different frame rates
    extern const float TIME_STEP;
}

#endif
