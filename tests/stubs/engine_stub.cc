/**
 * @author alvaro.zurinaga
 * @brief Provide only the engine calls needed by the headless game tests
 */

#include "AEEngine.h"

namespace
{
    bool keys[256] = {};
    float circleX = 0.0f;
    float circleY = 0.0f;
}

unsigned char AEInputKeyPressed(unsigned char key)
{
    return keys[key] ? 1 : 0;
}

void AEGfxCircle(float x, float y, float, unsigned, unsigned)
{
    circleX = x;
    circleY = y;
}

void AEGfxRectMinMax(float, float, float, float, float, unsigned)
{
}

unsigned AEGfxColor(unsigned r, unsigned g, unsigned b, unsigned a)
{
    return (a << 24) | (r << 16) | (g << 8) | b;
}

void AEGfxPrint(int, int, unsigned, const char*)
{
}

void EngineStub::reset()
{
    for (int i = 0; i < 256; ++i)
        keys[i] = false;
    circleX = 0.0f;
    circleY = 0.0f;
}

void EngineStub::setKey(unsigned char key, bool pressed)
{
    keys[key] = pressed;
}

float EngineStub::getCircleX()
{
    return circleX;
}

float EngineStub::getCircleY()
{
    return circleY;
}
