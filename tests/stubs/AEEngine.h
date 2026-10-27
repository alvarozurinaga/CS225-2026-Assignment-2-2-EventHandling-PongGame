/**
 * @author alvaro.zurinaga
 * @brief Provide only the engine calls needed by the headless game tests
 */

#ifndef TEST_AE_ENGINE_H
#define TEST_AE_ENGINE_H

enum
{
    VK_UP = 0x26,
    VK_DOWN = 0x28
};

/**
 * @brief Return the simulated key state
 */
unsigned char AEInputKeyPressed(unsigned char key);

/**
 * @brief Record the drawn ball position
 */
void AEGfxCircle(float x, float y, float radius, unsigned color, unsigned segments);

/**
 * @brief Provide rectangle drawing for the tests
 */
void AEGfxRectMinMax(float minX, float minY, float maxX, float maxY, float z, unsigned color);

/**
 * @brief Create a packed color
 */
unsigned AEGfxColor(unsigned r, unsigned g, unsigned b, unsigned a = 255);

/**
 * @brief Provide text drawing for the tests
 */
void AEGfxPrint(int x, int y, unsigned color, const char* text);

namespace EngineStub
{
    /**
     * @brief Reset simulated input and drawing state
     */
    void reset();

    /**
     * @brief Set a simulated key state
     */
    void setKey(unsigned char key, bool pressed);

    /**
     * @brief Return the last drawn circle horizontal position
     */
    float getCircleX();

    /**
     * @brief Return the last drawn circle vertical position
     */
    float getCircleY();
}

#endif
