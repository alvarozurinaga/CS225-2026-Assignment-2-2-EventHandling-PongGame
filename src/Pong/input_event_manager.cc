/**
 * @author alvaro.zurinaga
 * @brief Convert keyboard state into device-independent movement events
 */

#include "input_event_manager.h"
#include "pong_events.h"
#include <AEEngine.h>

InputEventManager::InputEventManager()
    : enabled(true)
{
}

void InputEventManager::setEnabled(bool newEnabled)
{
    enabled = newEnabled;
}

void InputEventManager::update()
{
    int direction = 0;
    if (enabled)
    {
        const bool up = AEInputKeyPressed('W') != 0 || AEInputKeyPressed(VK_UP) != 0;
        const bool down = AEInputKeyPressed('S') != 0 || AEInputKeyPressed(VK_DOWN) != 0;
        if (up)
            ++direction;
        if (down)
            --direction;
    }

    // A zero direction also sends an event so releasing a key stops movement
    // The event stays alive until the synchronous notification has finished
    InputEvent event(direction);
    notifyEvent(&event);
}
